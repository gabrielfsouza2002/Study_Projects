/*
    pescaria de MAC0420/MAC5744 - Pescaria

    Nome: Gabriel Ferreira de Souza Araujo
    NUSP: 12718100
 */

// Define a função main como a função a ser chamada quando a janela termina de carregar
window.onload = main;

// Variáveis globais
var ctx; // Contexto do canvas
const headerHeight = document.querySelector('h3').offsetHeight; // Altura do cabeçalho
const paragraphHeight = document.querySelector('p').offsetHeight; // Altura do parágrafo
var height = window.innerHeight - headerHeight - paragraphHeight - 20; // Altura do canvas ajustada
var width = window.innerWidth; // Largura do canvas
var canvas = document.getElementById('meucanvas'); // Referência ao elemento canvas
var jogando = false; // Variável para controlar se o jogo está em execução ou pausado


var circulos = []; // Array para armazenar as informações de cada círculo
var numCirculos = 10; // Defina aqui o número de círculos desejado
var alfaVel = 1; // Fator de multiplicação da velocidade
var corSorteada = sorteieCor(); // Cor aleatória para os círculos
const AREIA_ALT = 0.30; // Altura da faixa de areia
var arpaoBase = 30; // Largura da base do arpão
var arpaoAltura = 60; // Altura do arpão
var arpaoPosX = width / 2 - arpaoBase / 2; // Posição X inicial do arpão
var arpaoPosY = height * (1 - AREIA_ALT / 2) - arpaoAltura / 2; // Posição Y inicial do arpão
var arpaoMovimento = 35;
var bolhaAtiva = false; // Verifica se já há uma bolha ativa
var bolhaPosX; // Posição X da bolha
var bolhaPosY; // Posição Y da bolha
let bolhaVelY = 10; // Velocidade vertical da bolha

// Constante de FPS
const FPS = 60;

/**
 * Função principal responsável por inicializar o jogo.
 */
function main() {
    const canvas = document.getElementById('meucanvas'); // Referência ao elemento canvas
    ctx = canvas.getContext('2d'); // Obtenção do contexto 2D do canvas
    if (!ctx) alert("Não consegui abrir o contexto 2d :-( "); // Alerta se o contexto não puder ser obtido

    redimensionarCanvas(); // Redimensiona o canvas para ajustar ao tamanho da janela

    window.addEventListener('resize', redimensionarCanvas); // Listener para redimensionar o canvas quando a janela é redimensionada
    window.addEventListener('mousemove', moverArpaoComMouse); // Listener para mover o arpão com o mouse

    criarCirculos(); // Cria os círculos no canvas

    window.addEventListener('keydown', moverArpao); // Listener para mover o arpão com as teclas do teclado

    const jogarPausarBtn = document.getElementById('jogarPausarBtn'); // Botão para jogar/pausar o jogo
    const passoBtn = document.getElementById('passoBtn'); // Botão para avançar um passo no jogo

    jogarPausarBtn.addEventListener('click', togglePlayPause); // Listener para alternar entre jogar e pausar o jogo
    passoBtn.addEventListener('click', step); // Listener para avançar um passo no jogo

    redesenhe(); // Redesenha o canvas
}

/**
 * Função para alternar entre jogar e pausar o jogo.
 */
function togglePlayPause() {
    jogando = !jogando; // Inverte o estado da variável 'jogando'
    if (jogando) {
        document.querySelector('button').textContent = "Pausar"; // Altera o texto do botão para 'Pausar'
        document.querySelector('button').nextElementSibling.disabled = true; // Desabilita o botão de Passo
    } else {
        document.querySelector('button').textContent = "Jogar"; // Altera o texto do botão para 'Jogar'
        document.querySelector('button').nextElementSibling.disabled = false; // Habilita o botão de Passo
    }
}

/**
 * Função para avançar um passo quando o jogo está pausado.
 */
function step() {
    if (!jogando) { // Verifica se o jogo está pausado
        for (let i = 0; i < circulos.length; i++) { // Loop pelos círculos
            let circulo = circulos[i]; // Círculo atual
            circulo.posX += circulo.vx; // Atualiza a posição X do círculo de acordo com sua velocidade horizontal
            circulo.posY += circulo.vy; // Atualiza a posição Y do círculo de acordo com sua velocidade vertical
            circulo.angulo += circulo.velocidadeAngular; // Atualiza o ângulo do círculo

            // Verifica se o círculo colidiu com as bordas do canvas e, se sim, inverte sua direção
            if (circulo.posX < circulo.raio || circulo.posX >= width - circulo.raio) {
                circulo.vx *= -1;
                circulo.vix *= -1;
            }
            if (circulo.posY < circulo.raio || circulo.posY >= height * (1 - AREIA_ALT) - circulo.raio) {
                circulo.vy *= -1;
                circulo.viy *= -1;
            }
        }
    }
    console.log("O jogador pulou +1 passo");
}

/**
 * Função para atualizar a velocidade dos círculos com base na posição da barra de controle de velocidade.
 */
function updateVelocidade() {
    let velocidade = document.getElementById('velocidade').value; // Obtém o valor da barra de controle de velocidade
    alfaVel = parseFloat(velocidade); // Converte para número e armazena em alfaVel
    
    // Atualiza a velocidade de cada círculo de acordo com o valor de alfaVel
    for (let i = 0; i < circulos.length; i++) {
        let circulo = circulos[i]; // Círculo atual
        circulo.vx = circulo.vix * alfaVel; // Atualiza a velocidade horizontal do círculo
        circulo.vy = circulo.viy * alfaVel; // Atualiza a velocidade vertical do círculo
    }
}

/**
 * Função para mover o arpão com o mouse.
 * @param {MouseEvent} event - Evento de movimento do mouse.
 */
function moverArpaoComMouse(event) {
    if (jogando) { // Verifica se o jogo está em execução
        const mouseX = event.clientX - canvas.offsetLeft; // Obtém a posição X do mouse relativa ao canvas
        if (mouseX < 0) {
            arpaoPosX = 0; // Limita a posição X do arpão à borda esquerda do canvas
        } else if (mouseX > width) {
            arpaoPosX = width; // Limita a posição X do arpão à borda direita do canvas
        } else {
            arpaoPosX = mouseX; // Define a posição X do arpão como a posição X do mouse
        }
    }
    console.log("Arpão movido para posição (", arpaoPosX, ")");
}

/**
 * Função para mover o arpão com as teclas do teclado.
 * @param {KeyboardEvent} event - Evento de tecla pressionada.
 */
function moverArpao(event) {
    if (jogando) { // Verifica se o jogo está em execução
        if (event.key === 'a' && arpaoPosX > 0) {
            arpaoPosX -= arpaoMovimento; // Move o arpão para a esquerda
            console.log("Arpão movido para esquerda na posição (", arpaoPosX, ")");
        } else if (event.key === 'd' && arpaoPosX < width) {
            arpaoPosX += arpaoMovimento; // Move o arpão para a direita
            console.log("Arpão movido para direta na posição (", arpaoPosX, ")");
        } else if ((event.key === 's' || event.key === 'S') && !bolhaAtiva) {
            bolhaAtiva = true; // Ativa a bolha
            atirarBolha(); // Dispara a bolha
        }
    }
    
}

/**
 * Função para atirar a bolha verticalmente.
 */
function atirarBolha() {
    bolhaPosX = arpaoPosX; // Define a posição X da bolha como a posição X atual do arpão
    bolhaPosY = arpaoPosY - arpaoAltura; // Define a posição Y da bolha acima do arpão
    
    // Define um intervalo para mover a bolha para cima até que alcance a parte superior do canvas
    let bolhaInterval = setInterval(() => {
        bolhaPosY -= bolhaVelY; // Move a bolha para cima
        if (bolhaPosY <= 0) { // Verifica se a bolha alcançou a parte superior do canvas
            bolhaAtiva = false; // Desativa a bolha
            clearInterval(bolhaInterval); // Limpa o intervalo de tempo
        }
    }, 1000 / FPS); // Define o intervalo de tempo com base na taxa de quadros por segundo (FPS)
    console.log("Bolha atirada!");
}

/**
 * Função para desenhar o arpão.
 */
function desenheArpao() {
    ctx.fillStyle = "black"; // Define a cor preta para o arpão
    ctx.beginPath(); // Inicia o desenho do arpão
    ctx.moveTo(arpaoPosX, arpaoPosY + arpaoAltura / 2); // Move para a posição inicial do arpão
    ctx.lineTo(arpaoPosX + arpaoBase, arpaoPosY + arpaoAltura / 2); // Desenha a base do arpão
    ctx.lineTo(arpaoPosX + arpaoBase / 2, arpaoPosY - arpaoAltura / 2); // Desenha o corpo do arpão
    ctx.closePath(); // Finaliza o desenho do arpão
    ctx.fill(); // Preenche o arpão com a cor preta
}

/**
 * Função para desenhar a bolha.
 */
function desenharBolha() {
    ctx.fillStyle = 'rgb(255, 0, 0)'; // Define a cor vermelha para a bolha
    ctx.fillRect(bolhaPosX, bolhaPosY, 20, 20); // Desenha a bolha como um retângulo
}

/**
 * Função para verificar colisão entre a bolha e os círculos.
 */
function verificarColisaoBolha() {
    for (let i = 0; i < circulos.length; i++) { // Loop pelos círculos
        let circulo = circulos[i]; // Círculo atual
        let distancia = Math.sqrt((bolhaPosX - circulo.posX) ** 2 + (bolhaPosY - circulo.posY) ** 2); // Calcula a distância entre a bolha e o círculo
        if (distancia < circulo.raio + 10) { // Verifica se houve colisão entre a bolha e o círculo
            circulos.splice(i, 1); // Remove o círculo do array
            bolhaAtiva = false; // Desativa a bolha
            console.log("Peixe atingido!");
            break; // Sai do loop
        }
    }
}

/**
 * Função para criar os círculos.
 */
function criarCirculos() {
    for (let i = 0; i < numCirculos; i++) { // Loop para criar os círculos
        let cor = sorteieCor(); // Cor aleatória para o círculo
        let raio = sorteie_inteiro(10, 50); // Raio aleatório para o círculo
        let posX = sorteie_inteiro(raio, width - raio); // Posição X aleatória para o círculo
        let posY = sorteie_inteiro(raio, height * (1 - AREIA_ALT) - raio); // Posição Y aleatória para o círculo
        let vix = sorteie_inteiro(-5, 5); // Velocidade horizontal aleatória para o círculo
        let viy = sorteie_inteiro(-5, 5); // Velocidade vertical aleatória para o círculo
        if (vix == 0) vix = 1; // Garante que a velocidade horizontal não seja zero
        if (viy == 0) viy = 1; // Garante que a velocidade vertical não seja zero
        let vx = vix * alfaVel; // Velocidade horizontal ajustada com base no fator de multiplicação
        let vy = viy * alfaVel; // Velocidade vertical ajustada com base no fator de multiplicação
        let dx = 0; // Deslocamento horizontal
        let dy = 0; // Deslocamento vertical
        let angulo = sorteie_inteiro(0, 360); // Ângulo aleatório para o círculo
        let velocidadeAngular = sorteie_inteiro(-5, 5); // Velocidade angular aleatória para o círculo
        let tiposdepeixe = [4, 8, 16]; // Tipos de peixe
        let indice = sorteie_inteiro(0, tiposdepeixe.length); // Índice aleatório para escolher o tipo de peixe
        let N = tiposdepeixe[indice]; // Número de triângulos para aproximar o círculo

        circulos.push({ raio, posX, posY, vix, viy, vx, vy, dx, dy, angulo, velocidadeAngular, N, cor }); // Adiciona o círculo ao array
    }
    console.log("Peixes foram Criados. QTD: ", numCirculos);
}

/**
 * Função para redesenhar o canvas.
 */
function redesenhe() {
    ctx.clearRect(0, 0, width, height); // Limpa o canvas
    ctx.fillStyle = "blue"; // Define a cor azul para o mar
    ctx.fillRect(0, 0, width, height * (1 - AREIA_ALT)); // Desenha o mar
    ctx.fillStyle = "sandybrown"; // Define a cor areia para a praia
    ctx.fillRect(0, height * (1 - AREIA_ALT), width, height * AREIA_ALT); // Desenha a praia
    desenheArpao(); // Desenha o arpão
    
    for (let i = 0; i < circulos.length; i++) { // Loop pelos círculos
        let circulo = circulos[i]; // Círculo atual
        if (jogando) { // Verifica se o jogo está em execução
            circulo.posX += circulo.vx; // Atualiza a posição X do círculo de acordo com sua velocidade horizontal
            circulo.posY += circulo.vy; // Atualiza a posição Y do círculo de acordo com sua velocidade vertical
            circulo.angulo += circulo.velocidadeAngular; // Atualiza o ângulo do círculo
            
            // Verifica se o círculo colidiu com as bordas do canvas e, se sim, inverte sua direção
            if (circulo.posX - circulo.raio < 0 || circulo.posX + circulo.raio > width) {
                circulo.vx *= -1;
                circulo.vix *= -1;
            }
            if (circulo.posY - circulo.raio < 0 || circulo.posY + circulo.raio > height * (1 - AREIA_ALT)) {
                circulo.vy *= -1;
                circulo.viy *= -1;
            }
        }
        desenheCirculo(circulo.posX, circulo.posY, circulo.raio, circulo.N, circulo.cor); // Desenha o círculo
    }
    updateVelocidade(); // Atualiza a velocidade dos círculos

    if (bolhaAtiva) { // Verifica se há uma bolha ativa
        desenharBolha(); // Desenha a bolha
        verificarColisaoBolha(); // Verifica a colisão da bolha com os círculos
    }
    requestAnimationFrame(redesenhe); // Chama a função redesenhe novamente
}

/**
 * Função para desenhar um círculo aproximado por triângulos.
 * @param {number} x - Posição X do centro do círculo.
 * @param {number} y - Posição Y do centro do círculo.
 * @param {number} raio - Raio do círculo.
 * @param {number} N - Número de triângulos para aproximar o círculo.
 * @param {string} cor - Cor do círculo.
 */
function desenheCirculo(x, y, raio, N, cor) {
    ctx.beginPath(); // Inicia o desenho do círculo
    ctx.moveTo(x + raio, y); // Move para a posição inicial do primeiro triângulo
    for (let i = 1; i <= N; i++) { // Loop para desenhar os triângulos
        let theta = (i / N) * Math.PI * 2; // Calcula o ângulo do triângulo
        let nextX = x + raio * Math.cos(theta); // Calcula a próxima posição X do triângulo
        let nextY = y + raio * Math.sin(theta); // Calcula a próxima posição Y do triângulo
        ctx.lineTo(nextX, nextY); // Desenha o próximo lado do triângulo
    }
    ctx.closePath(); // Finaliza o desenho do círculo
    ctx.fillStyle = cor; // Define a cor do círculo
    ctx.fill(); // Preenche o círculo com a cor especificada
}

/**
 * Função para redimensionar o canvas.
 */
function redimensionarCanvas() {
    const headerHeight = document.querySelector('h3').offsetHeight; // Altura do cabeçalho
    const paragraphHeight = document.querySelector('p').offsetHeight; // Altura do parágrafo
    height = window.innerHeight - headerHeight - paragraphHeight - 20; // Altura do canvas ajustada
    width = window.innerWidth; // Largura do canvas
    canvas.width = width; // Define a largura do canvas
    canvas.height = height; // Define a altura do canvas
}

/**
 * Função para sortear uma cor RGB aleatória.
 * @returns {string} Cor no formato 'rgb(r,g,b)'.
 */
function sorteieCor() {
    var r = Math.floor(Math.random() * 256); // Componente vermelho (0-255)
    var g = Math.floor(Math.random() * 256); // Componente verde (0-255)
    var b = Math.floor(Math.random() * 100); // Componente azul (0-99)
    return `rgb(${r},${g},${b})`; // Retorna a cor no formato 'rgb(r,g,b)'
}

/**
 * Função para sortear um número inteiro entre min e max.
 * @param {number} min - Valor mínimo (inclusive).
 * @param {number} max - Valor máximo (exclusive).
 * @returns {number} Número inteiro aleatório.
 */
function sorteie_inteiro(min, max) {
    x = Math.floor(Math.random() * (max - min)) + min; // Calcula um número inteiro aleatório dentro do intervalo especificado
    return x; // Retorna o número inteiro aleatório
}
