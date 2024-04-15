x0 = 1.2;
h_values = 10.^(-20:1:0);
results = zeros(size(h_values));
theoretical_derivative = cos(x0); % Valor teórico da derivada em x0

% Cálculo da derivada aproximada e do erro absoluto para cada valor de h
approx_derivatives = zeros(size(h_values));
absolute_errors = zeros(size(h_values));
for i = 1:length(h_values)
    h = h_values(i);
    approx_derivative = (sin(h/2) / (h/2)) * cos(x0 + h/2);
    approx_derivatives(i) = approx_derivative;
    absolute_error = abs(approx_derivative - theoretical_derivative);
    absolute_errors(i) = absolute_error;
end

% Exibição dos resultados em forma de tabela
fprintf('h\t\tAbsolute error\n');
for i = 1:length(h_values)
    fprintf('%.1e\t%.6e\n', h_values(i), absolute_errors(i));
end

% A diferença na precisão entre nossos resultados e os resultados relatados no Exemplo 1.3 é devido ao fato de que nossa fórmula derivada evita erros de cancelamento. No Exemplo 1.3, a fórmula para aproximar a derivada usa sin(x0+h) - sin(x0), o que está sujeito a erros de cancelamento quando x0 + h e x0 estão próximos em valor. Os erros de cancelamento resultam em maiores erros nas aproximações. Em contraste, nossa fórmula derivada usasin(x0 + h/2) - sin(x0-h/2)  e evita erros de cancelamento ao ter uma estrutura mais estável, graças à manipulação trigonométrica que realizamos. Isso resulta em aproximações mais precisas da derivada, especialmente para valores pequenos de h.
