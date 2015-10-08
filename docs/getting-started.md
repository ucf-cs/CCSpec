---
layout: tervel_documentation
---

# Installing CCSpec

## System Requirements

Supported platforms:

*   Ubuntu Linux


## Downloading CCSpec

Clone CCSpec from the git repo:

{% highlight bash %}
$ git clone {{ site.gitrepo }}
{% endhighlight %}

## Building CCSpec

### Dependencies

* [Flex](http://sourceforge.net/projects/flex/files/)

* [Bison](ftp://prep.ai.mit.edu/pub/gnu/bison/)

### Building

{% highlight bash %}
$ cd CCSpec
$ make
$ make experiments
{% endhighlight %}

## Running CCSpec Experiments

{% highlight bash %}
$ cd CCSpec
$ ./run.sh experiments/IQueue/test.o
{% endhighlight %}


