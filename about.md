---
layout: tervel_about
---

# CCSpec

CCSpec is a Correctness Condition Specification tool that allows the user to check that their concurrent data structure meets a specified correctness condition. 
Our tool is built on top of the model checker CDSChecker and interprets annotations written in Scylla (SpeCification Language for Lockless Algorithms). 
CCSpec's language for specifying a correctness condition can accommodate any correctness condition that expects the concurrent data structure to behave equivalent to its sequential counterpart. 
The language enables a user to specify the conditions for which a method happens before another method through the happens-before relation. 
The specification is translated by a specialized interpreter which produces the legal sequential histories for the concurrent history. 
CCSpec generates all possible legal sequential histories based on the partial ordering on the method calls by the happens-before relation. 
The concurrent history of a particular execution is verified to meet the correctness condition if it can be mapped to a legal sequential history.  
