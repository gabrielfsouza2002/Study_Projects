function img_funcao = interpola_funcao (P = 1000, funcao = 1)
  % Cria as matrizes de pixels vazias para R, G e B
  R = zeros(P, P);
  G = zeros(P, P);
  B = zeros(P, P);

  % Calcula os valores das funções nos pontos correspondentes
  for i = 1:P
      for j = 1:P
          % Calcula as coordenadas (x, y) correspondentes ao ponto (i, j)
          x = i;
          y = j;

          % Calcula os valores das funções nos pontos (x, y)
          if (funcao == 1)
            valueR = sin(x);
            valueG = (sin(y) + sin(x))/2;
            valueB = sin(x);
          elseif (funcao == 2)
            valueR = 80*x*x;            #sin(x)*x;
            valueG = x/70;              #(sin(y) + sin(x))/8;
            valueB = cos(y);
          elseif (funcao == 3)
            valueR = sin(x)*x;
            valueG = (sin(y) + sin(x))/8;
            valueB = sin(x)*sin(y);
          else
            dis("Insira um número válido!");
          endif

          % Preenche as matrizes de pixels com os valores correspondentes
          R(i, j) = valueR;
          G(i, j) = valueG;
          B(i, j) = valueB;

      end
  end
  % Cria a imagem RGB combinando as três matrizes de pixels
  img = cat(3, R, G, B);

  % Exibe a imagem
  imshow(img);

  % Salva a imagem em um arquivo
  imwrite(uint8(imgcomprimida), "image.png");
  return
endfunction


