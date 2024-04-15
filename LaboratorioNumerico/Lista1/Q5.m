function Q5

    %QUESTÃO 5A)

    % Solicita ao usuário que insira os valores de x e n
    x = input('Por favor, insira os valores de x como um vetor: ');
    n = input('Por favor, insira o valor de n: ');

    % Calcula o tamanho de x
    tamanho_x = length(x);

    % Normaliza o vetor x
    normalizacao_x = normalize_to_fraction(x);

    % Realiza o arredondamento
    resultado = round_to_n_decimals(x ./ normalizacao_x, n);

    % Exibe o resultado final
    disp(resultado .* normalizacao_x);


    % QUESTÃO 5B)
    test_rounding_error(); % Chama a função para executar o teste
end

function rounded = round_to_n_decimals(x, n)
    if ~isscalar(n) || ~isnumeric(n) || n < 0 || floor(n) ~= n
        error('O número de casas decimais deve ser um valor escalar inteiro não negativo.');
    end
    % Inicializa a matriz de saída com o mesmo tamanho de x
    rounded = zeros(size(x));

    % Itera sobre os índices de x
    for cont = 1:length(x)
        value = x(cont);

        % Arredonda o valor para n dígitos decimais
        rounded(cont) = round_single_value(value, n);
    end
end


function rounded_value = round_single_value(value, n)
    % Converte o valor para uma string para manipular os dígitos individualmente
    str_value = num2str(value, ['%.' num2str(n) 'f']); % Formatando o número de casas decimais

    % Encontra a posição do ponto decimal na string
    decimal_point_index = strfind(str_value, '.');

    % Verifica se o valor é negativo
    is_negative = false;
    if str_value(1) == '-'
        is_negative = true;
        str_value = str_value(2:end);
        decimal_point_index = decimal_point_index - 1;
    end

    % Obtém os dígitos antes e depois do ponto decimal
    integer_part = str2double(str_value(1:decimal_point_index-1));
    decimal_part = str2double(str_value(decimal_point_index+1:end));

    % Concatena a parte inteira e decimal com o ponto decimal
    rounded_str = [num2str(integer_part) '.' num2str(decimal_part)];

    % Converte a string arredondada de volta para um número
    rounded_value = str2double(rounded_str);

    % Se o valor original era negativo, ajusta o sinal
    if is_negative
        rounded_value = -rounded_value;
    end
end
function normalizacao = normalize_to_fraction(x)
    % Inicializa o vetor de saída com o mesmo tamanho do vetor de entrada
    normalizacao = ones(size(x));

    % Itera sobre os elementos do vetor de entrada
    for i = 1:numel(x)
        % Ajusta o valor absoluto de x para ser menor que 1
        while abs(x(i)) > 1
            x(i) = x(i) / 10;
            normalizacao(i) = normalizacao(i) * 10;
        end
    end
end

function test_rounding_error
    n = 5;
    t = 0:0.002:1;
    tt = exp(-t) .* (sin(2*pi*t) + 2);

    normalizacao = normalize_to_fraction(tt);
    resultado = round_to_n_decimals(tt ./ normalizacao, n);
    rt = resultado .* normalizacao;

     % Calcula o erro de arredondamento
    round_err = (tt - rt) ./ tt;

    % Plota o erro de arredondamento
    plot(t, round_err, 'b-');
    title('Erro ao amostrar exp(-t)(sin(2\pi t)+2) em single precision');
    xlabel('t');
    ylabel('Erro de arredondamento');

    % Calcula o erro relativo máximo
    rel_round_err = max(abs(round_err)) / (eps('single')/2);

    % Mostra o valor do erro relativo máximo
    fprintf('O erro relativo máximo é aproximadamente: %f\n', rel_round_err);

end

Q5(); % Chama a função as

%  Quanto maior o valor de n, menor será a unidade de arredondamento e, consequentemente, menor será o erro de arredondamento. Portanto, conforme n aumenta, a escala vertical do gráfico tende a diminuir, indicando uma redução no erro de arredondamento.


