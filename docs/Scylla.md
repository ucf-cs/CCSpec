---
layout: tervel_documentation
---

# Scylla
Scylla is the first specification language that allows the user to express desirable properties of non-blocking data structures and algorithms. Scylla provides the user with the expressive power to verify correctness and progress guarantees, monitor performance, and select data structure functional properties that are most suitable for their programming needs. 

# Basic Usage
Scylla interprets annotations preceded by //#. 

## Keywords
*	begin{String method name} - Indicates the invocation of a method.
*	end{String method name} - Indicates the response of a method.
*	input{T params} - Indicates the input parameters to a method.
*	result{T val} - Indicates the return value of a method.