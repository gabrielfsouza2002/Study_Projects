%QUESTÃO 1C

x0 = 1.2;
f0 = sin(x0);
fp = cos(x0);

i = -20:0.5:0;
h = 10.^i;

% Calculando os erros absolutos
err = abs(fp - (sin(x0 + h) - sin(x0 - h)) ./ (2 * h));

% Calculando a estimativa do erro discretizado
d_err =  abs(fp)/6 .* h.*h;

% Plotando o gráfico em escala log-log
loglog(h, err, '-*');
hold on
loglog(h, d_err, 'r-.');
xlabel('h');
ylabel('Erro Absoluto');
legend('Erro Real', 'Estimativa do Erro Discretizado');
title('Erro Absoluto vs. h para a Nova Aproximação da Derivada');

%Nota-se que o erro discretizado e o real converge mais rapidamente que o erro discretizado do exemplo 1.3. Mas pelo problema do acumulo de erros computacionais chega um ponto em que ambos os gráficos começam a ter um comportamento caótico. O gráfico do exemplo começa a ter esse comportamente mais tarde para valores da ordem de h^-8, enquanto o gráfico do exercício começa a ter este comportamento para h da ordem de 10^-5. O resultado do gráfico do exercício nos mostra que conseguimos atingir um erro absoluto real menor (proximo de 10^-11) do que o do exemplo (próximo de 10^-9) sem a presença do comportamento caótico.
