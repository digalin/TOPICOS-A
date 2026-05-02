# mm 
# performs the matrix multiplication 
# input: m, n, r in N; A in R**{m x r}, B in R**{r x n} 
# output: C = A * B, C in R**{m x n} 
function C = mm(m, n, r, A, B) 
    if m <= 0 | n <= 0 | r <= 0 
        error("arguments 1, 2 and 3 must be greater than zero.");
    endif
    [rows, columns] = size(A); 
    if rows < m
        error("rows of argument 4 is less than argument 1.");
    endif
    if columns < r
        error("columns of argument 4 is less than argument 3.");
    endif
    [rows, columns] = size(B);
    if rows < r
        error("rows of argument 5 is less than argument 3.");
    endif
    if columns < n
        error("columns of argument 5 is less than argument 2.");
    endif
    C = zeros(m, n);
    for i = 1:m
        for j = 1:n
            for k = 1:r
                C(i, j) = C(i, j) + A(i, k) * B(k, j);
            endfor
        endfor
    endfor
endfunction
