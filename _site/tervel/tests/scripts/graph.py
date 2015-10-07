__author__ = 'stevenfeldman'
import sys
import pickle
import yaml
import os
import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

from matplotlib.backends.backend_pdf import PdfPages

print matplotlib.__version__, matplotlib.__file__

import seaborn as sns; sns.set(style="ticks", color_codes=True, rc={"lines.linewidth": .3})

# INSTALL FROM GIT LINKS!
runConfigs = {}
# Add <metric_name, functions names> here to allow 'CustomMetrics' to be loaded
def add_operation(data, name, obj):
    sum_t = 0
    sum_f = 0
    sum_p = 0
    for k in obj["totals"]:
        temp = int(obj["totals"][k])
        sum_t += temp
        if "Fail" in k:
            sum_f += temp
        if "Pass" in k:
            sum_p += temp

    temp = {"total:all": sum_t,
            "total:pass": sum_p,
            "total:fail": sum_f
            }

    Execution.add_key_val_pair(data, temp, name)
    Execution.add_key_val_pair(data, obj["totals"], name)


metric_functions =  {"operations": add_operation}


class Execution:
    @staticmethod
    def add_key_val_pair(data, set_src, prefix_=""):
        for s in set_src:
            res = prefix_ + ":" + s
            val = set_src[s]
            if type(val) is dict or type(val) is set:
                Execution.add_key_val_pair(data, val, res)
            elif res not in data:
                data[res] = val
            else:
                data[res] += val

    @staticmethod
    def add_metric(data, name, obj):
        if name in metric_functions:
            metric_functions[name](data, "metrics:" + name, obj)
        else:
            Execution.add_key_val_pair(data, obj, "metrics:" + name)

    @staticmethod
    def add_execution(data, obj):
        if "metrics" in obj:
            for c in obj["metrics"]:
                Execution.add_metric(data, c, obj["metrics"][c])


def load_file(fname):
    global runConfigs
    with open(fname, "r") as fin:
        obj = yaml.load(fin)

    test_config = obj["test_config"]
    alg_config = obj["alg_config"]
    temp = alg_config["run_config"].split(" ")
    alg_config["run_config"] = ""
    threads = float(obj["test_config"]["num_threads"])
    if "num_op_types" not in test_config:
        print "error log file missing num_op_types parameter, setting default to 1"
        op_types = 1
    else:
        op_types = int(test_config["num_op_types"])

    i = 0
    while i < len(temp):
        alg_config["run_config"] += "[%.2f%%:" % (float(temp[i]) / float(threads))
        i += 1
        for j in range(op_types):
            alg_config["run_config"] += " %d" % (int(temp[i]))
            i += 1
        alg_config["run_config"] += "]"
    runConfigs[alg_config["run_config"]] = 0

    data = {}
    data["CMD"] = obj["CMD"]
    data["key"] = ""
    Execution.add_key_val_pair(data, test_config, "test_config")
    Execution.add_key_val_pair(data, alg_config, "alg_config")

    if "metrics" in obj:
        for c in obj["metrics"]:
            Execution.add_metric(data, c, obj["metrics"][c])
        return data
    else:
        return None


def load_logs_from_dir(path):
    results = []
    for (dirpath, dirnames, filenames) in os.walk(path):
        num_files = len(filenames)
        c = 0
        for f in filenames:
            c += 1
            f = dirpath + "/" + f
            print "(" + str(c) + "/" + str(num_files) + "):  " + f
            if ".log" in f:
                res = load_file(f)
                if (res != None):
                    results.append(res)
        break
    return results



def custom_plot(fname, df_, x_key, y_keys, hue="key",  hue_keys = None, OUTPUT_DATA=False, disable_legend=True):
    plt.close('all')
    print fname

    if len(df_) == 0:
        print "No records for this test in this data set"
        return

    yid = 1
    for y_key in y_keys:
        print str(yid) + " : " + y_key

        # Output data
        if  OUTPUT_DATA:
            for t in [2, 4, 8, 16, 32, 64]:
                print "Threads: %d" %t

                df_t = df_
                temp = df_t[x_key] == t
                df_t = df_t[temp]

                s = "row/col"
                for k1 in hue_keys:
                    df_k1 = df_t
                    temp = df_k1[hue].str.contains(k1)
                    df_k1 = df_k1[temp]
                    x = df_k1[y_key].mean()
                    s += ", %s(%.2f)" %(k1,x)
                print s

                for k1 in  ["WaitFree", "Linux"]:
                    df_k1 = df_t
                    temp = df_k1[hue].str.contains(k1)
                    df_k1 = df_k1[temp]
                    x = df_k1[y_key].mean()
                    s = "%s(%.2f)" %(k1,x)

                    for k2 in hue_keys:
                        df_k2 = df_t
                        temp = df_k2[hue].str.contains(k2)
                        df_k2 = df_k2[temp]
                        # print len(df_k2)

                        y = df_k2[y_key].mean()
                        s += ", %.2f" %(100*(x-y)/y)
                    print s

        f, ax = plt.subplots(1, 1, figsize=(3.25, 1.75))
        ax = sns.barplot(x=x_key, y=y_key,
                            hue=hue, hue_order=hue_keys,
                            data=df_, ax=ax)


        # title = (y_key.split(":")[3]).title()
        # ax.set_title(title)
        ax.set_xlabel("Threads")

        # ax.set(ylim=(0, 3.5 * pow(10, 7)))
        ax.spines['left'].set_visible(False)
        ax.spines['right'].set_visible(False)
        ax.spines['top'].set_visible(False)
        ax.yaxis.set_ticks_position('left')
        ax.xaxis.set_ticks_position('bottom')
        # ax.set_ylabel("Operations")


        yid += 1

        if not disable_legend:
            figLegend = plt.figure(figsize = (6.25,.5))

            plt.figlegend(*ax.get_legend_handles_labels(),ncol=6, loc = 'center left')
            for item in ([ax.title, ax.xaxis.label, ax.yaxis.label] + ax.get_xticklabels() + ax.get_yticklabels()):
                item.set_fontsize(5)

            plt.savefig(fname+'_legend.pdf')
            plt.close()
            return
        else:
            # ax.legend_.remove()
            pass

        plt.savefig(fname + "_"+("_".join(y_key.split(":"))).title()+".pdf", bbox_inches='tight')  # saves the current figure into a pdf page
        plt.close()


def graph_on_x(df_, x_axis_):
    # Generates a Unique Key
    df_["key"] = df_.apply(lambda row: "", axis=1)
    for k in df_.keys():
        if k != x_axis_ and "metrics" not in k and k != "key" and k != "CMD":

            def func(row):
                temp = str(row[k])
                if temp != "nan":
                    i = k.rfind(":") + 1
                    return k[i:] + ":" + temp + "-"
                return ""
            df_["key"] += df_.apply(lambda row: func(row), axis=1)

    #Major Filters out tests we dont care about right now
    # df = df[(df["alg_config:run_config"].str.contains("100 0"))]
    # df = df[(df["test_config:num_threads"] == 2)]
    # df = df[(df["alg_config:ds_config:prefill"] == 16384)]
    # df = df[(df["alg_config:algorithm_name"].str.match("(Naive)").str.len() == False)]


#Generate Graphs

    #Minor Filtering
    temp_df = df
    # temp_df = temp_df[~(temp_df["alg_config:algorithm_name"].str.contains("Map"))] # Negation Example
    # temp_df = temp_df[(temp_df["alg_config:algorithm_name"].str.contains("(Stack)|(Map)"))] # Regex example
    temp_df = temp_df[(temp_df["alg_config:algorithm_name"].str.contains("Stack"))] # Standard example
    #Plot
    # custom_plot(<filename>, temp_df, <x_axis column name>, <list of y-value column names>)
        #Note filename gets the y_value column name appened
        #hue specified what to join
    custom_plot("test", temp_df, x_axis_, ["metrics:TERVELMETRICS:announcement_count"], hue = "alg_config:algorithm_name")

if __name__ == "__main__":
#Loads the data from the specified folder
    reprocess = False
    folder = "logs/1437938628/"
    pFile = folder + "cache_dataframe.p"
    pFile_rc = folder + "cache_runconfig.p"
    if reprocess or not os.path.exists(pFile) or not os.path.exists(pFile_rc):
        execution_results = load_logs_from_dir(folder)
        print "Elements:" + str(len(execution_results))
        df = pd.DataFrame(execution_results)

        pickle.dump(df, open(pFile, "wb"))
        pickle.dump(runConfigs, open(pFile_rc, "wb"))
    else:
        df = pickle.load(open(pFile, "rb"))
        runConfigs = pickle.load(open(pFile_rc, "rb"))

    print df.keys()

    # for k in df.keys():
    #     # Series(df.values.ravel()).unique()
    #     if "metrics" not in k and k != "key" and k != "CMD":
    #         print k
    #         print pd.Series(df[k].values.ravel()).unique()
    temp = (df["metrics:operations:per_thread"].values)
    exit()
# Example of replacing a column value in a row:
#     def rename_rows_col(val):
#         # val
#         if val == "old value":
#             return "new value"
#         else:
#             # print "Non matching value " + row
#             return val
#     col_name = "alg_config:run_config"
#     df[col_name] = df[col_name].map(lambda x: rename_rows_col(x))

    graph_on_x(df, "test_config:num_threads")


