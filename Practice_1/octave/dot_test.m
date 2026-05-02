# dot_test: dot function vs Octave operator
n_size = zeros(1, 1);
# t_dot = zeros(1, 1);
t_op = zeros(1, 1);
n = [2^21 2^22 2^23 2^24 2^25 2^26];
n_length = length(n);
for i = 1:n_length
  n_size = [n_size; n(i)];
  x = ones(n(i), 1);
  y = ones(n(i), 1);
#  sum_dot = 0;
  sum_op = 0;
  for j = 1:7
#    tic;
#    c = dot(n(i), x, y);
#    sum_dot = sum_dot + toc;
    tic;
    c = x' * y;
    sum_op = sum_op + toc;
  endfor
#  t_dot = [t_dot; (sum_dot / 7)];
  t_op = [t_op; (sum_op / 7)]
  clear x, y;
endfor
data = [n_size(2:n_length + 1) t_op(2:n_length + 1)]
save "dot.dat" data;
clear all;
