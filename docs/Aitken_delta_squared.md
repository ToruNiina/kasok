# Aitken's delta-squared process

An implementation of [Aitken's delta-squared process](https://en.wikipedia.org/wiki/Aitken%27s_delta-squared_process).

It provides the following functions.

```cpp
template<typename Function, typename Tolerance, typename UInt>
/* the same type as Function returns */
aitken(Function&& f, Tolerance&& tolerance, UInt& iteration);

template<typename FirstIterator, typename LastIterator, typename Tolerance>
/* the same type as Function returns */
aitken(FirstIterator& first, LastIterator last, Tolerance&& tolerance);

template<typename Function, typename Tolerance, typename UInt>
/* the same type as Function returns */
aitken_sum(Function&& f, Tolerance&& tolerance, UInt& iteration);

template<typename FirstIterator, typename LastIterator, typename Tolerance>
/* the same type as Function returns */
aitken_sum(FirstIterator& first, LastIterator last, Tolerance&& tolerance);
```

## calculating limit of a sequence

The following functions calculates the limit of a given sequence.

```cpp
template<typename Function, typename Tolerance, typename UInt>
/* the same type as Function returns */
aitken(Function&& f, Tolerance&& tolerance, UInt& iteration);

template<typename FirstIterator, typename LastIterator, typename Tolerance>
/* the same type as Function returns */
aitken(FirstIterator& first, LastIterator last, Tolerance&& tolerance);
```

## calculating limit of sum of a sequence

The following functions automatically calculates the sum of a given sequence.
The usage is the same as the functions that calculates a limit.

```cpp
template<typename Function, typename Tolerance, typename UInt>
/* the same type as Function returns */
aitken_sum(Function&& f, Tolerance&& tolerance, UInt& iteration);

template<typename FirstIterator, typename LastIterator, typename Tolerance>
/* the same type as Function returns */
aitken_sum(FirstIterator& first, LastIterator last, Tolerance&& tolerance);
```
