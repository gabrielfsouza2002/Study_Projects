function imagemDescomprimida = decompress (imagemComprimida='imgComprimida.png', h=1, k=3, metodo=2)
    imagem = imread(imagemComprimida);
    tamanho = size(imagem);
    imagemDescomprimida = zeros(tamanho(1), tamanho(2), tamanho(3));
    if (metodo == 1)
        imagemDescomprimida = interpolacaoBilinear(k, im2double(imagem));
        imwrite(imagemDescomprimida, 'imgDescomprimida.png');
    elseif (metodo == 2)
        imagemDescomprimida = interpolacaoBicubica(k, im2double(imagem));
        imwrite(imagemDescomprimida, 'imgDescomprimida.png');
    endif
    return;
endfunction

function expandirImagem = interpolacaoBilinear (k, imagemComprimida)
    tamanho = size(imagemComprimida);
    p = tamanho(1) + (tamanho(1)-1)*k;
    expandirImagem = zeros(p, p, 3);
    i=1;
    j=1;
    R1 = imagemComprimida(:,:,1);
    G1 = imagemComprimida(:,:,2);
    B1 = imagemComprimida(:,:,3);
    while (i < tamanho(1))
        while(j < tamanho(2))
            R2 = _interpolacaoBilinear(k, R1(i:i+1, j:j+1));
            G2 = _interpolacaoBilinear(k, G1(i:i+1, j:j+1));
            B2 = _interpolacaoBilinear(k, B1(i:i+1, j:j+1));
            expandirImagem((i*(k+1))-k:(i+1)*(k+1)-k, (j*(k+1))-k:(j+1)*(k+1)-k, 1) = R2;
            expandirImagem((i*(k+1))-k:(i+1)*(k+1)-k, (j*(k+1))-k:(j+1)*(k+1)-k, 2) = G2;
            expandirImagem((i*(k+1))-k:(i+1)*(k+1)-k, (j*(k+1))-k:(j+1)*(k+1)-k, 3) = B2;
            j = j + 1;
        endwhile
        j = 1;
        i = i + 1;
    endwhile
    return;
endfunction

function interpolacao = _interpolacaoBilinear(k, funcao)
    x1=0.; x2=1; y1=0; y2=1;
    M = [x2*y2, -x2*y1, -x1*y2, x1*y1;
           -y2,     y1,     y2,   -y1;
           -x2,     x2,     x1,   -x1;
             1,     -1,     -1,     1];
    matriz = transpose(M * funcao);
    interpolacao = zeros(k+2, k+2);
    funcao = reshape(funcao, [4,1]);
    i=1; j=1;
    while(i <= k + 2)
        while(j <= k + 2)
            x = (j-1)/(k+1);
            y = (i-1)/(k+1);
            polinomio = [1; x; y; x*y];
            pixel = matriz * polinomio;
            interpolacao(i,j) = pixel;
            j = j + 1;
        endwhile
        j = 1;
        i = i + 1;
    endwhile
    return;
endfunction

function expandirImagem = interpolacaoBicubica(k, imagemComprimida)
    imagem = imagemComprimida;
    derivada_x_img = imagem_dx(imagem);
    derivada_y_img = imagem_dy(imagem);
    der_parcialXY_imagem = imagem_dy(derivada_x_img);
    tamanho = size(imagemComprimida);
    p = tamanho(1) + (tamanho(1)-1)*k;
    expandirImagem = zeros(p, p, 3);
    i=1; j=1;
    while (i < tamanho(1))
        while(j < tamanho(2))
            R1 = cat(1, cat(2, imagem(i:i+1, j:j+1, 1), derivada_x_img(i:i+1, j:j+1, 1)), cat(2, derivada_y_img(i:i+1, j:j+1, 1), der_parcialXY_imagem(i:i+1, j:j+1, 1)));
            G1 = cat(1, cat(2, imagem(i:i+1, j:j+1, 2), derivada_x_img(i:i+1, j:j+1, 2)), cat(2, derivada_y_img(i:i+1, j:j+1, 2), der_parcialXY_imagem(i:i+1, j:j+1, 2)));
            B1 = cat(1, cat(2, imagem(i:i+1, j:j+1, 3), derivada_x_img(i:i+1, j:j+1, 3)), cat(2, derivada_y_img(i:i+1, j:j+1, 3), der_parcialXY_imagem(i:i+1, j:j+1, 3)));
            R2 = _interpolacaoBicubica(k, R1);
            G2 = _interpolacaoBicubica(k, G1);
            B2 = _interpolacaoBicubica(k, B1);
            expandirImagem((i*(k+1))-k:(i+1)*(k+1)-k, (j*(k+1))-k:(j+1)*(k+1)-k, 1) = R2;
            expandirImagem((i*(k+1))-k:(i+1)*(k+1)-k, (j*(k+1))-k:(j+1)*(k+1)-k, 2) = G2;
            expandirImagem((i*(k+1))-k:(i+1)*(k+1)-k, (j*(k+1))-k:(j+1)*(k+1)-k, 3) = B2;
            j = j + 1;
        endwhile
        j = 1;
        i = i + 1;
    endwhile
    return;
endfunction

function interpolacao = _interpolacaoBicubica(k, funcao)
    M = [ 1,  0,  0,  0;
          0,  0,  1,  0;
         -3,  3, -2, -1;
          2, -2,  1,  1];
    interpolacao = zeros(k+2, k+2);
    matriz = M * funcao;
    matriz = matriz * transpose(M);
    i = 1;
    j = 1;
    while(i <= k + 2)
        while(j <= k + 2)
            x = (j-1)/(k+1);
            X = [1, x, x*x, x*x*x];
            y = (i-1)/(k+1);
            Y = transpose([1, y, y*y, y*y*y]);
            interpolacao(i, j) = X * matriz * Y;
            j = j + 1;
        endwhile
        j = 1;
        i = i + 1;
    endwhile
    interpolacao = transpose(interpolacao);
    return;
endfunction

function derivada_x_img = imagem_dx(imagem)
    tamanho = size(imagem);
    tamanho_y = tamanho(1);
    tamanho_x = tamanho(2);
    derivada_x_img = zeros(tamanho_y, tamanho_x, 3);
    derivada_x_img(2:tamanho_x-1, :) = imagem(3:tamanho_x, :)-imagem(1:tamanho_x-2, :);
    derivada_x_img(1, :) = imagem(2,  :)-imagem(1, :);
    derivada_x_img(tamanho_x, :) = imagem(tamanho_x, :)-imagem(tamanho_x-1, :);
    return;
endfunction


function derivada_y_img = imagem_dy(imagem)
    tamanho = size(imagem);
    tamanho_y = tamanho(1);
    tamanho_x = tamanho(2);
    derivada_y_img = zeros(tamanho_y, tamanho_x, 3);
    derivada_y_img(:, 2:tamanho_y-1) = imagem(:, 3:tamanho_y)-imagem(:, 1:tamanho_y-2);
    derivada_y_img(:, 1) = imagem(:,  2)-imagem(:, 1);
    derivada_y_img(:, tamanho_y) = imagem(:, tamanho_y)-imagem(:, tamanho_y-1);
    return;
endfunction

