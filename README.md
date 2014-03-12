### Augmented Intrusive Binary Search Trees


#### Overview

This fork provides basic hooks in the existing implementation of Boost
Intrusive binary search trees that are sufficient to implement
**intrusive interval trees**, as decribed, e.g., in *Introduction to
Algorithms* by Cormen et al.

A separate package provides a basic implementation of intrusive
interval trees.


#### Type of Augmented Data

The extra data maintained at each node of the tree must satisfy the
following requirement:

  **The extra data stored at node `n` can only depend on the
    _multiset_ of values stored in the subtree rooted at `n`.**

So, this data may not depend on values stored elsewhere in the tree.
Also, it may not depend on the _structure_ of the subtree rooted at
`n`, only on the multiset of values in that subtree. An example of
data that satisfies the requirement above is the size of the subtree
rooted at `n`.


#### Internals

Inside Boost Intrusive, the inner workings of a binary search tree are
implemented as a set of generic algorithms in
`bstree_algorithms.hpp`. The way in which these algorithms access
tree-related data stored at each node (such as a parent node pointer)
is controlled by a `Node_Traits` struct.

This package simply checks whether the `Node_Traits` contains two
special static methods, with the following signatures:

    void clone_extra_data(node_ptr dest, const_node_ptr src)
    void recompute_extra_data(node_ptr n)

If *both* of these function exist, each time the tree structure is
changed, they are called in order to maintain the extra data at the
nodes. If either one of them does not exist, empty functions are used
instead (which the compiler should optimize out).

The `clone_extra_data()` function is used whenever a tree node `dest`
is copy-created from a tree node `src`.

The `recompute_extra_data()` is the core of the augmentation. This
function takes a single parameter, a node `n`. The function may assume
that the extra data of all of `n`'s children is up to date. Ideally,
this function should consult the value stored at `n` along with the
extra data of `n`'s children, and update the extra data of `n`, all in
constant time.


#### Usage

To use these augmented trees, the path to the `include/` folder of
this package must appear before boost in the include path given to the
compiler. E.g.:

    g++ -I <path-to-this-repo>/include -I <path-to-boost> [...]


#### Disclaimer

The code in this repository depends on the *implementation* of Boost
Intrusive binary search trees. In order for it to be stable, the
repository is a fork of the entire Boost Intrusive library. By using
the code in this repository, you are effectively pinning down the
Boost Intrusive library to the latest version available in this
repository. Boost libraries that to not depend on Boost Intrusive are
unaffected.
