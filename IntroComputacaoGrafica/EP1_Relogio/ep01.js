 /* ==================================================
        ep01.js

        Nome: Gabriel Ferreira de Souza Araujo
        NUSP: 12718100

        Ao preencher esse cabeçalho com o meu nome e o meu número USP,
        declaro que todas as partes originais desse exercício programa (EP)
        foram desenvolvidas e implementadas por mim e que portanto não 
        constituem desonestidade acadêmica ou plágio.
        Declaro também que sou responsável por todas as cópias desse
        programa e que não distribui ou facilitei a sua distribuição.
        Estou ciente que os casos de plágio e desonestidade acadêmica
        serão tratados segundo os critérios divulgados na página da 
        disciplina.
        Entendo que EPs sem assinatura devem receber nota zero e, ainda
        assim, poderão ser punidos por desonestidade acadêmica.
        
        Abaixo descreva qualquer ajuda que você recebeu para fazer este
        EP.  Inclua qualquer ajuda recebida por pessoas (inclusive
        monitores e colegas). Com exceção de material da disciplina, caso
        você tenha utilizado alguma informação, trecho de código,...
        indique esse fato abaixo para que o seu programa não seja
        considerado plágio ou irregular.

    ================================================== */

var gInterface = {
    inicio: 0,
    tempoSelecionado: 0,
    cronometroRodando: false,
    modoCrono: true,
    paused: false,
    pausedTime: 0
};

function main() {
    construaInterface();
    gereProximoQradro();
}

function construaInterface() {
    gInterface.startStopButton = document.getElementById('btStartStop');
    gInterface.clock = document.getElementById('clock');
    gInterface.clock2 = document.getElementById('clock2');
    gInterface.cronoTimerButton = document.getElementById('btCronoTimer');
    gInterface.pauseRunButton = document.getElementById('btPauseRun');
    gInterface.adicionarNumero = document.getElementsByClassName('teclado')
}

function adicionarNumero(numero) {

    if (gInterface.pauseRunButton.value != "Pause"){
        console.log("Tecla Desabilitada")
    }
 
    else if (Math.floor(gInterface.tempoSelecionado/1000000) == 0){
        
        gInterface.tempoSelecionado = (gInterface.tempoSelecionado * 10) + numero;
        atualizarBloco1();
        console.log("Botão: ", numero, gInterface.tempoSelecionado)
    }
}

function atualizarBloco1() {
    let minutos = Math.floor((gInterface.tempoSelecionado % 1000000)/10000);
    let segundos = Math.floor((gInterface.tempoSelecionado % 10000)/100);
    let milissegundos = gInterface.tempoSelecionado % 100;

    if (minutos >= 60) {
        minutos = 59
    }
    if(segundos >= 60){
        segundos = 59
    }

    let tempoFormatado = `${f2(minutos)}:${f2(segundos)}:${f2(milissegundos)}`;
    gInterface.clock.innerText = `Tempo: ${tempoFormatado}`;
}

function limparBloco1() {

    if (gInterface.pauseRunButton.value != "Pause"){
        console.log("Tecla Desabilitada")
    }
    else{
    gInterface.tempoSelecionado = 0;
    atualizarBloco1();
    console.log("Clear -> 00:00:00")
    }
}

function f2(x) {
    return ('00' + x).slice(-2);
}

function alternarModo() {

    gInterface.cronoTimerButton.value = gInterface.modoCrono ? "Timer" : "Crono";
    
    if (gInterface.modoCrono){
        console.log("Modo Timer Ativado")
    }
    else{
        console.log("Modo Cronometro Ativado")
    }
    gInterface.modoCrono = !gInterface.modoCrono;
}

function startStop() {

    if (gInterface.startStopButton.value === "Start") {
        gInterface.startStopButton.value = "Stop";
        gInterface.inicio = Date.now();

        gInterface.cronometroRodando = true;
        gInterface.paused = false;
        gInterface.pausedTime = 0;
        console.log("Start")
        
    } else {
        gInterface.startStopButton.value = "Start";
        gInterface.cronometroRodando = false;

        gInterface.paused = false;
        gInterface.pausedTime = 0;
        gInterface.clock2.innerText = "00 : 00 : 00";
        console.log("Stop")
    }
}

function pauseRun() {

    if (!gInterface.paused) {
        gInterface.pauseRunButton.value = "Run";
        gInterface.paused = true;
        gInterface.pausedTime = Date.now();
        console.log("Pausado")
    } else {
        gInterface.pauseRunButton.value = "Pause";
        gInterface.paused = false;
        gInterface.inicio += (Date.now() - gInterface.pausedTime);
        console.log("Rodando")
    }

}

function converterMilissegundos(milissegundos) {
    // Convertendo milissegundos em segundos
    var segundosTotal = milissegundos / 1000;

    // Calculando minutos
    var minutos = Math.floor(segundosTotal / 60);
    var segundosRestantes = segundosTotal % 60;

    // Calculando milissegundos
    var milissegundosFinais = Math.floor((segundosRestantes - Math.floor(segundosRestantes)) * 1000);

    // Formatando e imprimindo o resultado
    return(

        `${f2(minutos)} : ${f2(Math.floor(segundosRestantes))} : ${f2(Math.floor(milissegundosFinais))}`
    );
}

function gereProximoQradro() {

    let now = Date.now();
    let dt = now - gInterface.inicio;
    let minutos = 0
    let segundos = 0
    let milissegundos = 0
    
    let totalms = (gInterface.tempoSelecionado%100) + Math.floor((gInterface.tempoSelecionado%10000)/100)*1000 + Math.floor((gInterface.tempoSelecionado)/10000)*60000

    if (gInterface.cronometroRodando && !gInterface.paused) {
        if (gInterface.modoCrono) {

            milissegundos = Math.floor(dt / 10) % 100;
            dt = Math.floor(dt / 1000);
            minutos = Math.floor(dt / 60);
            segundos = dt - minutos * 60;

            if (parseInt( `${f2(minutos)}${f2(segundos)}${f2(milissegundos)}`) >= gInterface.tempoSelecionado && gInterface.tempoSelecionado != 0){
                startStop()
            }
            gInterface.clock2.innerText = `${f2(minutos)} : ${f2(segundos)} : ${f2(milissegundos)}`;
            

        } else {
            let tempoRestante = totalms - dt;

            if (tempoRestante <= 0) {
                tempoRestante = 0;
                startStop(); // Se o tempo acabar, pare o cronômetro
            }

            gInterface.clock2.innerText =converterMilissegundos(tempoRestante);
        }
    }

    window.requestAnimationFrame(gereProximoQradro);
}

window.onload = main;
