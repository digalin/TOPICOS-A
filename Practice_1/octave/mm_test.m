# mm_test
n_size = zeros(1, 1);
# t_mm = zeros(1, 1);
t_op = zeros(1, 1);
n = [2^3 2^4 2^5 2^6 2^7 2^8 2^9 2^10 2^11 2^12];
n_length = length(n);
for i = 1:n_length
    n_size = [n_size; n(i)];
    A = ones(n(i));
    B = ones(n(i));
#    sum_mm = 0;
    sum_op = 0;
    for j = 1:7
#        tic;
#        C = mm(n(i), n(i), n(i), A, B);
#        sum_mm = sum_mm + toc;
        tic;
        C = A * B;
        sum_op = sum_op + toc;
    endfor
#    t_mm = [t_mm; (sum_mm / 7)];
    t_op = [t_op; (sum_op / 7)]
    clear A, B;
endfor
data = [n_size(2:n_length + 1) t_op(2:n_length + 1)]
save "mm.dat" data;
clear all;
