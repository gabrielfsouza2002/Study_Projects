function comprimirImagem = comprimir(imgOriginal='imagem.png', k=3)
    img = imread(imgOriginal);
    sz1 = size(img);
    comprimirImagem = img(k:k:end-1, k:k:end-1, :);
    sz2 = size(comprimirImagem);
    imwrite(comprimirImagem, 'imgComprimida.png');
endfunction
