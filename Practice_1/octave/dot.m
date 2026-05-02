# dot
# forms the dot product of two vectors
# input: n in N; x, y in R**n
# output: c = x’ * y, c in R
function c = dot(n, x, y)
    if n <= 0
        error("argument 1 must be greater than zero.");
    endif
    if length(x) < n
        error("size of argument 2 is less than argument 1.");
    endif
    if length(y) < n
        error("size of argument 3 is less than argument 1.");
    endif
    c = 0;
    for i = 1:n
        c = c + x(i) * y(i);
    endfor
endfunction
