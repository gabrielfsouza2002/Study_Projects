% Definindo a função
f = @(x) sin(x);

% Definindo o ponto de avaliação
x0 = 1.2;

% Valor exato da derivada em x0
exact_derivative = cos(x0);

% Valores de h a serem testados
h_values = [0.1, 0.01, 0.001, 1e-4, 1e-7];

% Inicializando vetores para armazenar os erros
approx_errors = zeros(size(h_values));
original_errors = [4.716676e-2, 4.666196e-3, 4.660799e-4, 4.660256e-5, 4.619326e-8];

% Calculando os erros da aproximação proposta
for i = 1:length(h_values)
    h = h_values(i);
    approx_derivative = (f(x0 + h) - f(x0 - h)) / (2 * h);
    approx_errors(i) = abs(approx_derivative - exact_derivative);
end

% Criando a tabela
fprintf('h\t\tAprox. Error\t\tOriginal Error\n');
fprintf('-------------------------------------------\n');
for i = 1:length(h_values)
    fprintf('%.1e\t%.8f\t%.8f\n', h_values(i), approx_errors(i), original_errors(i));
end

% A nova aproximação da derivada parece produzir erros significativamente menores em comparação com a aproximação normal da derivada, especialmente para valores menores de H. Para h na ordem de 10^-4 e 10^-7, a nova aproximação atinge erros de aproximação muito próximos de zero. Isso sugere que a nova abordagem pode ser mais precisa para valores pequenos de h, conforme esperado.
