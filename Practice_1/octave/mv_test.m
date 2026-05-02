# mv_test: mv function vs Octave operator
n_size = zeros(1, 1);
# t_mv = zeros(1, 1);
t_op = zeros(1, 1);
n = [2^10 2^11 2^12 2^13 2^14 2^15];
n_length = length(n);
for i = 1:n_length
    n_size = [n_size; n(i)];
    A = ones(n(i));
    x = ones(n(i), 1);
#    sum_mv = 0;
    sum_op = 0;
    for j = 1:7
        tic;
#        y = mv(n(i), n(i), A, x);
#        sum_mv = sum_mv + toc; tic;
        y = A * x;
        sum_op = sum_op + toc;
        endfor
#    t_mv = [t_mv; (sum_mv / 7)];
    t_op = [t_op; (sum_op / 7)]
    clear A, x;
endfor
data = [n_size(2:n_length + 1) t_op(2:n_length + 1)]
save "mv.dat" data; 
clear all;
