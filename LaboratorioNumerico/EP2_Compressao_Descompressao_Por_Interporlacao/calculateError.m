function ERRO = calculateError(imgemOriginal='imagem.png', imagemDescomprimida='imgDescomprimida.png')
    imagem = im2double(imread(imgemOriginal));
    decompressed = im2double(imread(imagemDescomprimida));

    erro = decompressed-imagem;
    R = norm(erro(:,:,1), 2) / norm(imagem(:,:,1), 2);
    G = norm(erro(:,:,2), 2) / norm(imagem(:,:,2), 2);
    B = norm(erro(:,:,3), 2) / norm(imagem(:,:,3), 2);
    ERRO = (R+G+B)/3;
    return;
endfunction
