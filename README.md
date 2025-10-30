
[!spreadsheet](tests.png)

[!spreadsheet](https://docs.google.com/spreadsheets/d/116KYmO580Z54Oe_s_p5Hut8hCsS4nybSSYqyommqGUs/edit?gid=0#gid=0)


Description
This project tests different sum algorithms to see how accurate and fast they are with arrays of different sizes.
The arrays have half of the elements with high values and half with very small values.
This is used to show how rounding errors can appear when summing large and small numbers together.

The program tests arrays with sizes from 2^10 (1,024 elements) to 2^27 (134,217,728 elements).
For each array, it calculates the correct (accurate) sum and compares it with the result from the do_sum() function.
It also measures how much time the calculation takes.
This helps to see how accuracy and performance change when the array gets bigger.

Floating-point numbers can’t represent every decimal value exactly, and when we keep adding small numbers to large ones, those small values can get lost because of rounding.
 This is why the standard sum becomes less accurate for very large arrays.
Kahan and Knuth methods fix this by compensating for those small rounding errors. They track the small bits that would otherwise be lost and add them back in future steps.
Because of that, these methods have almost no error, even when the array is huge.
Using long double also helps since it stores more digits internally, reducing rounding effects — though it can be slower.
