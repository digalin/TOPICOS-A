# mv
# performs the matrix-vector multiplication
# input: m, n in N; A in R**{m x n}, x in R**n
# output: y = A * x, y in R**m
function y = mv(m, n, A, x)
  if m <= 0 | n <= 0
    error("arguments 1 and 2 must be greater than zero.");
  endif
  [rows, columns] = size(A);
  if rows < m
    error("rows of argument 3 is less than argument 1.");
  endif
  if columns < n
    error("columns of argument 3 is less than argument 2.");
  endif
  if length(x) < n
    error("size of argument 4 is less than argument 2.");
  endif
  y = zeros(m, 1);
  for i = 1:m
    for j = 1:n
      y(i) = y(i) + A(i, j) * x(j);
    endfor
  endfor
 endfunction
