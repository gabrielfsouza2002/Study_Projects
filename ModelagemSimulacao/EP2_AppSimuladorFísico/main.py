from kivy.app import App
from kivy.lang import Builder
from kivy.utils import platform
from kivy.properties import ObjectProperty
from kivy.clock import Clock

from kivy.uix.floatlayout import FloatLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.uix.popup import Popup
from kivy.uix.image import Image
from kivy.uix.label import Label

from kivy_garden.graph import Graph, LinePlot
from plyer import accelerometer

import csv
import os

import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import find_peaks

Builder.load_file("ep2.kv")

# converte a velocidade de m/s para km/h
def ms2kh(ms):
    return(3.6 * ms)

# calcula o pace médio
def kh2Pace(kmh):
    hkm = 60 * 1.0 / kmh
    
    mins = int(hkm)
    segs = int((hkm - mins) * 60)
    
    return(mins, segs)

# estima as posições e as velocidades pelo método de euler em diversos
# instantes de tempo dada uma aceleração média
def euler(t0, tf, dt, x0, v0, aceleracaoMedia):
    
    # inicializa com os valores iniciais  
    vatual = v0
    xatual = x0
    tatual = t0

    # vetores em que serão armazenados os valores encontrados
    v = []
    x = []
    t = []

    while(tatual <= tf):
        # adiciona os últimos valores encontrados de velocidade posição e tempo
        v.append(vatual)
        x.append(xatual)
        t.append(tatual)
        
        # calcula os valores atuais de posição velocidade e tempo
        xatual = xatual + (vatual * dt)
        vatual = vatual + (aceleracaoMedia * dt)
        tatual += dt

    return(t, x, v)

# inicializa o vetor de estados
def initstateVector(x0, v0, t0):
    return np.array([x0, v0, t0])

# função que extrai os dados obtidos somente de uma variável
def extractSVTrajectory(svt, i):
    aux = np.array(svt)
    return(aux[:, i])

# função rates que está calculando os valores assumindo que a aceleração causada pela
# resistência do ar é o valor mostrado pelo acelerômetro
def rates_acelerometro(s, dt, a):
    r0 = s[1] * dt
    r1 = (1 - a) * (9.8) * dt
    r2 = dt
    return(np.array([r0, r1, r2]))

# função que atualiza o vetor de estados assumindo que a aceleração causada pela
# resistência do ar é o valor mostrado pelo acelerômetro
def updateStateVector_acelerometro(s, dt, a):
    return s + rates_acelerometro(s, dt, a)

class TelaPrincipal(FloatLayout):
    pass

class BotoesLaterais(BoxLayout):
    pass

class Telas(ScreenManager):
    pass

class Acelerometro(Screen):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)        
        self.grafico = None

        self.eixoOx = None
        self.eixoOy = None
        self.eixoOz = None

        self.contador_tempo = 0
        self.contador_tempo_grafico = 0
        self.intervalo_tempo = 0.05
        self.tempo = []
        self.aceleracaoX = []
        self.aceleracaoY = []
        self.aceleracaoZ = []      

        self.dadosCSV = []
        
        self.funcao_inicial = None
        self.parou = 0
        
    # Prepara para plotar o gráfico com os dados coletados do acelerômetro
    def iniciar(self):
        self.reiniciar_grafico() # limpa os dados coletados antes, caso existam
        self.contador_tempo = 0
        self.dadosCSV = []

        self.ids.botao_iniciar.state = "down"
        self.ids.botao_iniciar.disabled = True

        self.ids.botao_parar.text = "Parar"
        self.parou = 0
    
        if(platform == "android"): # Verificar se a plataforma é um celular ou um computador
            accelerometer.enable()

        # atualizar o gráfico a cada 'intervalo_tempo' segundos
        self.funcao_inicial = Clock.schedule_interval(self.atualizar_grafico, self.intervalo_tempo)

    # Criar o objeto gráfico e coloca ele na tela.
    def iniciar_grafico(self):
        self.grafico = Graph(xmin = 0, xmax = 5, ymin = -5, ymax = 5, border_color = [1, 1, 1, 1])
        self.grafico.background_color = [0, 0, 0, 1]

        self.eixoOx = LinePlot(line_width = 1, color = [1,0,0,1])
        self.eixoOy = LinePlot(line_width = 1, color = [0,1,0,1])
        self.eixoOz = LinePlot(line_width = 1, color = [0,0,1,1])

        self.grafico.add_plot(self.eixoOx)
        self.grafico.add_plot(self.eixoOy)
        self.grafico.add_plot(self.eixoOz)

        self.ids.grafico.add_widget(self.grafico)

    # Atualiza o gráfico com os dados do acelerômetro
    def atualizar_grafico(self, *args): 
        if(platform == "android"):
            dados_acelerometro = accelerometer.acceleration[:3]
            if(dados_acelerometro != (None, None, None)):
                # Obs: os dados do acelerômetro devem ser divididos pelo valor de gravidade (g = 9.806 m/s^2)
                x = dados_acelerometro[0] / 9.806
                y = dados_acelerometro[1] / 9.806
                z = dados_acelerometro[2] / 9.806
            
                self.aceleracaoX.append(x)
                self.aceleracaoY.append(y)
                self.aceleracaoZ.append(z)
                self.tempo.append(self.contador_tempo_grafico)
        
                t = self.contador_tempo
                R = (x * x + y * y + z * z) ** 0.5 # cálculo da acelaração resultante
        
                # salva os dados obtidos em uma lista (que poderá ser salva em um arquivo csv)
                self.dadosCSV.append([round(t, 3), round(x, 3), round(y, 3), round(z, 3), round(R, 3)])
        
                self.contador_tempo_grafico += self.intervalo_tempo
                self.contador_tempo += self.intervalo_tempo
                 
        # se já ocupou todo gráfico
        if(len(self.aceleracaoX) * self.intervalo_tempo > 5):
            self.limpar_dados_grafico() # reinicia o gráfico, mas não reinicia os dados.

        self.eixoOx.points = [(self.tempo[i], self.aceleracaoX[i]) for i in range(len(self.aceleracaoX))]
        self.eixoOy.points = [(self.tempo[i], self.aceleracaoY[i]) for i in range(len(self.aceleracaoY))]
        self.eixoOz.points = [(self.tempo[i], self.aceleracaoZ[i]) for i in range(len(self.aceleracaoZ))]

    # Reinicia o desenho do gráfico na tela. OBS: não apaga os dados, apenas o gráfico
    def reiniciar_grafico(self):
        self.ids.grafico.clear_widgets()
        self.limpar_dados_grafico()
        self.iniciar_grafico()
    
    # OBS: Limpa o gráfico da tela, mas não apaga os dados
    def limpar_dados_grafico(self):
        self.contador_tempo_grafico = 0
        self.tempo = []
    
        self.aceleracaoX = []
        self.aceleracaoY = []
        self.aceleracaoZ = []

    # Para de atualizar o gráfico
    def parar(self):
        if(not self.parou):
            self.funcao_inicial.cancel()

            self.ids.botao_iniciar.state = "normal"
            self.ids.botao_iniciar.disabled = False

            self.ids.botao_parar.text = "Salvar"   
            self.parou = 1

        else:
            self.mostrar_salvar()

    # Mostra as opções de onde salvar o arquivo csv com os dados do acelerômetro
    def mostrar_salvar(self):
        conteudo = SalvarArquivo(salvar = self.salvar, cancelar = self.fechar_popup)
        
        caminho = "."

        if(platform == "android"):
            from android.permissions import request_permissions, Permission
            request_permissions([Permission.READ_EXTERNAL_STORAGE, Permission.WRITE_EXTERNAL_STORAGE])
            caminho = "/sdcard"

        conteudo.ids.filechooser.path = caminho
        self._popup = Popup(title = "Salvar arquivo", content = conteudo, size_hint = (.9, .9))
        self._popup.open()
    
    # Salva os dados do acelerômetro num csv com cada componente da aceleração e a resultante
    def salvar(self, path, filename):
        with open(os.path.join(path, filename) + ".csv", "w", encoding = "UTF8", newline = "") as file:
            arquivo_csv = csv.writer(file)
            arquivo_csv.writerow(["time", "gFx", "gFy", "gFz", "tgF"])
            arquivo_csv.writerows(self.dadosCSV)            

        self.fechar_popup()

    def fechar_popup(self):
        self._popup.dismiss()

class SalvarArquivo(FloatLayout):
    salvar = ObjectProperty(None)
    nome_arquivo = ObjectProperty(None)
    cancelar = ObjectProperty(None)

class LerDados(Screen):
    # Mostra o pop-up para escolher o arquivo de onde carregar os dados
    def mostrar_carregar(self):
        conteudo = CarregarArquivo(carregar = self.carregar, cancelar = self.fechar_popup)

        caminho = "."

        if(platform == "android"):
            from android.permissions import request_permissions, Permission
            request_permissions([Permission.READ_EXTERNAL_STORAGE, Permission.WRITE_EXTERNAL_STORAGE])
            caminho = "/sdcard"

        conteudo.ids.filechooser.path = caminho

        self._popup = Popup(title = "Carregar arquivo", content = conteudo, size_hint = (.9, .9))
        self._popup.open()
    
    # Carrega um csv com os dados coletados por um acelerômetro.
    def carregar(self, path, filename):
        app = App.get_running_app()
        
        app.aceleracao = []
        app.tempo = []

        with open(os.path.join(path, filename[0]), "r") as file:
            arquivo_csv = csv.reader(file, delimiter = ",")

            next(arquivo_csv, None) # pular a primeira linha!
            
            for linha in arquivo_csv:
                app.tempo.append(float(linha[0]))
                app.aceleracao.append(float(linha[4]))

        self.fechar_popup()

    def fechar_popup(self):
        self._popup.dismiss()

class CarregarArquivo(FloatLayout):
    carregar = ObjectProperty(None)
    cancelar = ObjectProperty(None)

class QuedaLivre(Screen):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        app = App.get_running_app() # pega valores gerados em outras telas.
        
        # lê os dados carregados em outras telas.
        self.aceleracao = app.aceleracao
        self.tempo = app.tempo
        self.tempoDaQueda = self.tempo
        self.aceleracaoNaQueda = self.aceleracao

        self.t0 = 0
        self.tf = 0

        # valor padrão
        self.numDeAmostras = 10

    def grafico_inicial(self):
        app = App.get_running_app()
        
        # lê os dados carregados
        self.aceleracao = app.aceleracao
        self.tempo = app.tempo
        self.tempoDaQueda = self.tempo
        self.aceleracaoNaQueda = self.aceleracao

        indiceT0 = 0
        indiceTf = len(self.aceleracao) - 1

        # caso o usuário digite valores para o início e o fim do movimento, pega esses valores.
        if(self.ids.inicioQL.text != "" and self.ids.fimQL.text):
            self.t0 = float(self.ids.inicioQL.text)
            self.tf = float(self.ids.fimQL.text)

            # pega os indices correspondentes ao t0 e o tf inseridos pelo usuário
            for i in range(len(self.tempo)):
                if (self.tf < self.tempo[i]):
                    indiceTf = i
                    break
            
            for i in range(len(self.tempo)):
                if (self.t0 < self.tempo[i]):
                    indiceT0 = i
                    break

        # ------- gráfico com todos os dados obtidos do experimento e com início e fim marcados -------
        fig, ax = plt.subplots()
        plt.plot(self.tempo[1:-1], self.aceleracao[1:-1], label = "Dados do acelerômetro")
        plt.plot([self.tempo[indiceT0], self.tempo[indiceTf]], [1, 1], "v", label = "Começo e Fim do percurso")
        plt.title("Dados do acelerômetro")
        ax.set_xlabel("Tempo (s)")
        ax.set_ylabel("Resultante (força g)")
        ax = plt.gca()
        ax.legend()
        plt.savefig("QuedaLivre.png")
        wimg = Image(source = "QuedaLivre.png", allow_stretch = True, keep_ratio = True)
        wimg.reload()

        # apaga os widgets para o caso de já ter um gráfico e coloca o novo gráfico no lugar
        self.ids.dados.clear_widgets()
        self.ids.dados.add_widget(wimg)

    def zoomNaQueda(self):

        # caso o usuário digite
        if(self.ids.inicioQL.text != "" and self.ids.fimQL.text != ""):
            self.t0 = float(self.ids.inicioQL.text)
            self.tf = float(self.ids.fimQL.text)
            self.tempoDaQueda = []
            self.aceleracaoNaQueda = []
        
        # caso o usuário digite
        if(self.ids.quantAmostras.text != ""):
            self.numDeAmostras = int(self.ids.quantAmostras.text)

        # pega os valores de tempo e aceleração entre t0 e tf
        for i in range(len(self.tempo)):
            if(self.tf < self.tempo[i]):
                break

            if(self.t0 < self.tempo[i]):
                self.tempoDaQueda.append(self.tempo[i])
                self.aceleracaoNaQueda.append(self.aceleracao[i])

        # pega amostras da aceleração em alguns pontos para usar no método de euler
        espacoEntreAmostras = len(self.tempoDaQueda) / self.numDeAmostras

        # pega o indice das amostras
        indAmostras = [round(ii * espacoEntreAmostras) for ii in range(self.numDeAmostras)]

        # ------- gráfico da queda com as amostras -------

        fig, ax = plt.subplots()
        plt.plot(self.tempoDaQueda, self.aceleracaoNaQueda, label = "Dados do acelerômetro")
        plt.plot([self.tempoDaQueda[ii] for ii in indAmostras], [self.aceleracaoNaQueda[ii] for ii in indAmostras], "v", label = "Pontos para amostrar a aceleração")
        plt.title("Dados do acelerômetro: zoom na queda")
        ax.set_xlabel("Tempo (s)")
        ax.set_ylabel("Resultante (força g)")
        ax.legend()

        # cria uma imagem com o gráfico e um widget com a imagem
        plt.savefig("QLZoom.png")
        wimg = Image(source = "QLZoom.png", allow_stretch = True, keep_ratio = True)
        wimg.reload()

        # apaga os widgets para o caso de já ter um gráfico e coloca o novo gráfico no lugar
        self.ids.dados.clear_widgets()
        self.ids.dados.add_widget(wimg)

    def gerarDados(self):
        # caso o usuário digite
        if(self.ids.quantAmostras.text != ""):
            self.numDeAmostras = int(self.ids.quantAmostras.text)

        # pega amostras da aceleração em alguns pontos para usar no método de euler
        espacoEntreAmostras = len(self.tempoDaQueda) / self.numDeAmostras

        # pega o indice das amostras
        indAmostras = [round(ii * espacoEntreAmostras) for ii in range(self.numDeAmostras)]
        
        # aproximar a função da velocidade com Euler
        stateVectorTraj_acelerometro = []
        dts = np.diff([self.tempo[i] for i in indAmostras])

        stateVector_acelerometro = initstateVector(0, 0, self.tempoDaQueda[0])
        stateVectorTraj_acelerometro.append(list(stateVector_acelerometro))

        # calcula as velocidades e posições pelo método de euler
        for ii in range(len(dts)):
            stateVector_acelerometro = updateStateVector_acelerometro(stateVector_acelerometro, dts[ii], self.aceleracaoNaQueda[indAmostras[ii]])
            stateVectorTraj_acelerometro.append(list(stateVector_acelerometro))

        tempoVector = extractSVTrajectory(stateVectorTraj_acelerometro, 2)
        posiVector_acelerometro = extractSVTrajectory(stateVectorTraj_acelerometro, 0)
        velVector_acelerometro = extractSVTrajectory(stateVectorTraj_acelerometro, 1)

        # cálculo da velocidade média
        distQueda = posiVector_acelerometro[-1] - posiVector_acelerometro[0]
        tempoQueda = tempoVector[-1] - tempoVector[0]
        velocidadeMedia = distQueda / tempoQueda

        # ------- gráfico da velocidade -------

        # gera o gráfico da velocidade estimada pelo método de euler
        fig, ax = plt.subplots()
        plt.plot(tempoVector, velVector_acelerometro, "o", label = "Velocidade estimada")
        
        plt.title("Velocidade na queda")
        ax.set_xlabel("Tempo (s)")
        ax.set_ylabel("Velocidade estimada (m/s)")
        ax.legend(loc = 1)

        # plota os dados do acelêrometro
        ax1 = ax.twinx()
        ax1.plot(self.tempoDaQueda, self.aceleracaoNaQueda, label = "Dados do acelerômetro", color = "green")
        ax1.set_ylabel("Força g (m/s^2)")
        ax1.legend(loc = 2)

        # cria uma imagem com o gráfico e um widget com a imagem
        plt.savefig("VelocidadeQL.png")
        wimg = Image(source = "VelocidadeQL.png", allow_stretch = True, keep_ratio = True)
        wimg.reload()

        # apaga os widgets para o caso de já ter um gráfico e coloca o novo gráfico no lugar
        self.ids.dados.clear_widgets()
        self.ids.dados.add_widget(wimg)

        # ------- gráfico da posição -------

        # gera o gráfico da posição estimada pelo método de euler
        fig, ax = plt.subplots()
        plt.plot(tempoVector, posiVector_acelerometro, "o", label = "Posição estimada")
        plt.title("Posição na queda")
        ax.set_xlabel("Tempo (s)")
        ax.set_ylabel("Posição estimada (m)")
        ax.legend(loc = 1)

        # plota os dados do acelêrometro
        ax1 = ax.twinx()
        ax1.plot(self.tempoDaQueda, self.aceleracaoNaQueda, label = "Dados do acelerômetro", color = "green")
        ax1.set_ylabel("Força g (m/s^2)")
        ax1.legend(loc = 2)

        # cria uma imagem com o gráfico e um widget com a imagem
        plt.savefig("PosicaoQL.png")
        wimg = Image(source = "PosicaoQL.png", allow_stretch = True, keep_ratio = True)
        wimg.reload()

        # coloca o gráfico no lugar
        self.ids.dados.add_widget(wimg)
        
        # ------- dados gerais obtidos ------

        textBox = BoxLayout(size_hint_y = "0.3", orientation = "vertical")
        lText = Label(text = "Sumário de dados do experimento:", font_size = 24, text_size = self.size, halign = "center", valign = "center")
        lVelo = Label(text = f"Velocidade média do objeto (m/s): {round(velocidadeMedia, 2)}", font_size = 24, text_size = self.size, halign = "left", valign = "center", pos_hint = {"x": 0.1})
        lPosi = Label(text = f"Distância percorrida pelo objeto (m): {round(distQueda, 2)}", font_size = 24, text_size = self.size, halign = "left", valign = "center", pos_hint = {"x": 0.1})

        textBox.clear_widgets()
        textBox.add_widget(lText)
        textBox.add_widget(lVelo)
        textBox.add_widget(lPosi)

        self.ids.dados.add_widget(textBox)

class MRU(Screen):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        app = App.get_running_app()
        
        # lê os dados carregados
        self.aceleracao = app.aceleracao
        self.tempo = app.tempo
        self.tempoNoMRU = self.tempo
        self.aceleracaoNoMRU = self.aceleracao

        self.picos = []
        self.t0 = 0
        self.tf = 0

        # valores padrões
        self.tamanhoPasso = 0.9
        self.proem = 0.7
        self.dist = 3

    def grafico_inicial(self):
        app = App.get_running_app()
        
        # lê os dados carregados
        self.aceleracao = app.aceleracao
        self.tempo = app.tempo
        self.tempoNoMRU = self.tempo
        self.aceleracaoNoMRU = self.aceleracao
        
        indiceT0 = 0
        indiceTf = len(self.aceleracao) - 1  

        # caso o usuário digite
        if(self.ids.inicioMRU.text != "" and self.ids.fimMRU.text):
            self.t0 = float(self.ids.inicioMRU.text)
            self.tf = float(self.ids.fimMRU.text)

            # pega os indices correspondentes ao t0 e o tf inseridos pelo usuário
            for i in range(len(self.tempo)):
                if(self.tf < self.tempo[i]):
                    indiceTf = i
                    break
            
            for i in range(len(self.tempo)):
                if(self.t0 < self.tempo[i]):
                    indiceT0 = i
                    break
                
        # ------- gráfico com todos os dados obtidos do experimento e com início e fim marcados -------
        fig, ax = plt.subplots()
        plt.plot(self.tempo, self.aceleracao, label = "Dados do acelerômetro")
        plt.plot([self.tempo[indiceT0], self.tempo[indiceTf]], [1, 1], "v", label = "Começo e Fim do percurso")
        plt.title("Dados do acelerômetro")
        ax.set_xlabel("Tempo (s)")
        ax.set_ylabel("Resultante (força g)")
        ax = plt.gca()
        ax.legend()
        plt.savefig("MRU.png")
        wimg = Image(source = "MRU.png", allow_stretch = True, keep_ratio = True)
        wimg.reload()

        # apaga os widgets para o caso de já ter um gráfico e coloca o novo gráfico no lugar
        self.ids.dados.clear_widgets()
        self.ids.dados.add_widget(wimg)
    
    def zoomNoMRU(self):
        # caso o usuário digite
        if(self.ids.inicioMRU.text != "" and self.ids.fimMRU.text != ""):
            self.t0 = float(self.ids.inicioMRU.text)
            self.tf = float(self.ids.fimMRU.text)
            self.tempoNoMRU = []
            self.aceleracaoNoMRU = []

        # pega os valores de tempo e aceleração entre t0 e tf
        for i in range(len(self.tempo)):
            if (self.tf < self.tempo[i]):
                break

            if (self.t0 < self.tempo[i]):
                self.tempoNoMRU.append(self.tempo[i])
                self.aceleracaoNoMRU.append(self.aceleracao[i])

        # caso o usuário digite um valor para a proeminência, pega esse valor.
        if(self.ids.proemMRU.text != ""):
            self.proem = float(self.ids.proemMRU.text)

        # caso o usuário digite um valor para a distância entre os picos, pega esse valor.
        if(self.ids.distMRU.text != ""):
            self.dist = float(self.ids.distMRU.text)

        # gera o gráfico dos dados obtidos pelo acelerometro marcando os passos
        peaks, _ = find_peaks(self.aceleracaoNoMRU, distance = self.dist, prominence = self.proem)
        
        # ignora o último
        peaks = peaks[0:-1]

        self.picos = peaks

        # ------- gráfico do mru com os picos -------

        fig, ax = plt.subplots()
        plt.plot(self.tempoNoMRU, self.aceleracaoNoMRU, label = "Dados do acelerômetro: zoom no MRU")
        plt.plot([self.tempoNoMRU[i] for i in peaks], [self.aceleracaoNoMRU[i] for i in peaks], "x", label = "Passos")
        plt.title("Dados do acelerômetro: zoom no MRU")
        ax.set_xlabel("Tempo (s)")
        ax.set_ylabel("Resultante (força g)")
        ax.legend()

        # cria uma imagem com o gráfico e um widget com a imagem
        plt.savefig("MRUZoom.png")
        wimg = Image(source = "MRUZoom.png", allow_stretch = True, keep_ratio = True)
        wimg.reload()

        # apaga os widgets para o caso de já ter um gráfico e coloca o novo gráfico no lugar
        self.ids.dados.clear_widgets()
        self.ids.dados.add_widget(wimg)
    
    def gerarDados(self):

        # ------- obtém dados do mru -------

        peaks, _ = find_peaks(self.aceleracaoNoMRU, distance = self.dist, prominence = self.proem)

        self.picos = peaks

        primeiroPasso = self.picos[0]
        ultimoPasso = self.picos[-1]

        # acelerações do intervalo

        mru = np.asarray(self.aceleracaoNoMRU[primeiroPasso:ultimoPasso])

        # tempos do intervalo que caminhou
        mruTempo = np.asarray(self.tempoNoMRU[primeiroPasso:ultimoPasso])
        mruTempo -= mruTempo[0]

        # caso o usuário digite um valor para a proeminência, pega esse valor
        if(self.ids.proemMRU.text != ""):
            self.proem = float(self.ids.proemMRU.text)

        # caso o usuário digite um valor para a distância entre os picos, pega esse valor
        if(self.ids.distMRU.text != ""):
            self.dist = float(self.ids.distMRU.text)

        peaks, _ = find_peaks(mru, distance = self.dist, prominence = self.proem)

        self.picos = peaks

        # caso o usuário digite
        if(self.ids.tamanhoPasso.text != ""):
            self.tamanhoPasso = float(self.ids.tamanhoPasso.text)

        # quantidade de passos
        nPassos = len(self.picos)

        # calcula quantidade de passos e distância total
        distanciaTotal = nPassos * self.tamanhoPasso

        # calcula tempo médio de cada passo e tempo total
        tempoPasso = np.average(np.diff(mruTempo[self.picos]))
        tempoTotal = nPassos * tempoPasso

        # cálculo da velocidade média (usando v = d / t)
        velocidadeMedia = (distanciaTotal) / (tempoTotal)
        
        ind = np.arange(0, nPassos) 
        
        # posições dos passos
        x = self.tamanhoPasso * ind
        # tempo dos passos
        t = tempoPasso * ind
        
        # posição inicial
        x0 = x[0]
        # tempo inicial
        t0 = t[0]
        # tempo final
        tf = t[-1]

        # obtém as posições estimadas pelo método de euler
        # obs: no MRU, a acelaração média é 0
        tEuler, xEuler, _ = euler(t0, tf, tempoPasso, x0, velocidadeMedia, 0)

        # salva dados obtidos
        distMRU = xEuler[-1] - xEuler[0]
        tempoMRU = tEuler[-1] - tEuler[0]
        velocidadeMediaMRU = distMRU / tempoMRU
        paceMinsMRU, paceSegsMRU = kh2Pace(ms2kh(velocidadeMediaMRU))

        # ------- gráfico da posição -------

        # gera o gráfico da posição estimada pelo método de euler
        fig, ax = plt.subplots()
        plt.plot(tEuler, xEuler, "ro", label = "Estimado: Euler")
        plt.title(f"Posição no MRU")
        plt.xlabel("Tempo (s)")
        plt.ylabel("Posição estimada (m)")
        ax = plt.gca()
        ax.legend()

        # cria uma imagem com o gráfico e um widget com a imagem
        plt.savefig("MRU2.png")
        wimg = Image(source = "MRU2.png", allow_stretch = True, keep_ratio = True)
        wimg.reload()

        # apaga os widgets para o caso de já ter um gráfico e coloca o novo gráfico no lugar
        self.ids.dados.clear_widgets()
        self.ids.dados.add_widget(wimg)

        # ------- dados gerais obtidos ------

        textBox = BoxLayout(size_hint_y = "0.5", orientation = "vertical")
        lText1 = Label(text = "Sumário de dados do experimento:", font_size = 24, text_size = self.size, halign = "center", valign = "center")
        lPosi = Label(text = f"Distância percorrida (m): {round(distMRU, 2)}", font_size = 24, text_size = self.size, halign = "left", valign = "center", pos_hint = {"x": 0.1})
        lTempo = Label(text = f"Tempo transcorrido (s): {round(tempoMRU, 1)}", font_size = 24, text_size = self.size, halign = "left", valign = "center", pos_hint = {"x": 0.1})
        lVelo = Label(text = f"Velocidade média no MRU (m/s):  {round(velocidadeMediaMRU,2)}", font_size = 24, text_size = self.size, halign = "left", valign = "center", pos_hint = {"x": 0.1})
        lPassos = Label(text = f"Número de passos: {nPassos}", font_size = 24, text_size = self.size, halign = "left", valign = "center", pos_hint = {"x": 0.1})
        lPace = Label(text = f"Pace médio no MRU (min/km): {str(paceMinsMRU)} min {paceSegsMRU} s por km", font_size = 24, text_size = self.size, halign = "left", valign = "center", pos_hint = {"x": 0.1})

        textBox.clear_widgets()
        textBox.add_widget(lText1)
        textBox.add_widget(lPosi)
        textBox.add_widget(lTempo)
        textBox.add_widget(lVelo)
        textBox.add_widget(lPassos)
        textBox.add_widget(lPace)
        
        self.ids.dados.add_widget(textBox)

class MUV(Screen):

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        app = App.get_running_app()
        
        # lê os dados carregados
        self.aceleracao = app.aceleracao
        self.tempo = app.tempo
        self.tempoNoMUV = self.tempo
        self.aceleracaoNoMUV = self.aceleracao

        self.picos = []
        self.t0 = 0
        self.tf = 0

        # valores padrões
        self.tamanhoPasso = 0.9
        self.veloIni = 0
        self.dist = 5
        self.proem = 3

    def grafico_inicial(self):
        app = App.get_running_app()

        # lê os dados carregados
        self.aceleracao = app.aceleracao
        self.tempo = app.tempo
        self.tempoNoMRU = self.tempo
        self.aceleracaoNoMRU = self.aceleracao

        indiceT0 = 0
        indiceTf = len(self.aceleracao) - 1  

        # caso o usuário digite valores de t0 e tf para o MUV, pega esses valores
        if(self.ids.inicioMUV.text != "" and self.ids.fimMUV.text):
            self.t0 = float(self.ids.inicioMUV.text)
            self.tf = float(self.ids.fimMUV.text)

            # pega os indices correspondentes ao t0 e o tf inseridos pelo usuário
            for i in range(len(self.tempo)):
                if (self.tf < self.tempo[i]):
                    indiceTf = i
                    break
            
            for i in range(len(self.tempo)):
                if(self.t0 < self.tempo[i]):
                    indiceT0 = i
                    break
        
        # ------- gráfico com todos os dados obtidos do experimento e com início e fim marcados -------
        fig, ax = plt.subplots()
        plt.plot(self.tempo, self.aceleracao, label = "Dados do acelerômetro")
        plt.plot([self.tempo[indiceT0], self.tempo[indiceTf]], [1, 1], "v", label = "Começo e Fim do percurso")
        plt.title("Dados do acelerômetro")
        ax.set_xlabel("Tempo (s)")
        ax.set_ylabel("Resultante (força g)")
        ax = plt.gca()
        ax.legend()
        plt.savefig("MUV.png")
        wimg = Image(source = "MUV.png", allow_stretch = True, keep_ratio = True)
        wimg.reload()

        # apaga os widgets para o caso de já ter um gráfico e coloca o novo gráfico no lugar
        self.ids.dados.clear_widgets()
        self.ids.dados.add_widget(wimg)
    
    def zoomNoMUV(self):
        # caso o usuário digite
        if(self.ids.inicioMUV.text != "" and self.ids.fimMUV.text != ""):
            self.t0 = float(self.ids.inicioMUV.text)
            self.tf = float(self.ids.fimMUV.text)
            self.tempoNoMUV = []
            self.aceleracaoNoMUV = []

        # pega os valores de tempo e aceleração entre t0 e tf
        for i in range(len(self.tempo)):
            if (self.tf < self.tempo[i]):
                break

            if (self.t0 < self.tempo[i]):
                self.tempoNoMUV.append(self.tempo[i])
                self.aceleracaoNoMUV.append(self.aceleracao[i])

        # caso o usuário digite um valor para a proeminênica, pega esse valor
        if (self.ids.proemMUV.text != ""):
            self.proem = float(self.ids.proemMUV.text)

        # caso o usuário digite um valor para a distância entre os picos, pega esse valor
        if (self.ids.distMUV.text != ""):
            self.dist = float(self.ids.distMUV.text)

        # gera o gráfico dos dados obtidos pelo acelerometro marcando os passos
        peaks, _ = find_peaks(self.aceleracaoNoMUV, distance = self.dist, prominence = self.proem)
        
        # ignora o último
        peaks = peaks[0:-1]

        self.picos = peaks

        # ------- gráfico do muv com os picos -------
        fig, ax = plt.subplots()
        plt.plot(self.tempoNoMUV, self.aceleracaoNoMUV, label = "Dados do acelerômetro: zoom no MRU")
        plt.plot([self.tempoNoMUV[i] for i in peaks], [self.aceleracaoNoMUV[i] for i in peaks], "x", label = "Passos")
        plt.title("Dados do acelerômetro: zoom no MUV")
        ax.set_xlabel("Tempo (s)")
        ax.set_ylabel("Resultante (força g)")
        ax.legend()

        # cria uma imagem com o gráfico e um widget com a imagem
        plt.savefig("MUVZoom.png")
        wimg = Image(source = "MUVZoom.png", allow_stretch = True, keep_ratio = True)
        wimg.reload()

        # apaga os widgets para o caso de já ter um gráfico e coloca o novo gráfico no lugar
        self.ids.dados.clear_widgets()
        self.ids.dados.add_widget(wimg)
    
    def gerarDados(self):
        
        # ------- obtém dados do muv -------

        peaks, _ = find_peaks(self.aceleracaoNoMUV, distance = self.dist, prominence = self.proem)

        self.picos = peaks

        primeiroPasso = self.picos[0]
        ultimoPasso = self.picos[-1]

        # acelerações do intervalo
        muv = np.asarray(self.aceleracaoNoMUV[primeiroPasso:ultimoPasso])

        # tempos do intervalo que caminhou
        muvTempo = np.asarray(self.tempoNoMUV[primeiroPasso:ultimoPasso])
        muvTempo -= muvTempo[0]

        # caso o usuário digite um valor de proeminência, pega esse valor
        if(self.ids.proemMUV.text != ""):
            self.proem = float(self.ids.proemMUV.text)

        # caso o usuário digite um valor para a distância entre os picos, pega esse valor.
        if(self.ids.distMUV.text != ""):
            self.dist = float(self.ids.distMUV.text)

        peaks, _ = find_peaks(muv, distance = self.dist, prominence = self.proem)

        self.picos = peaks

        # caso o usuário digite um valor para o tamanho do passo, pega esse valor.
        if (self.ids.tamPassoMUV.text != ""):
            self.tamanhoPasso = float(self.ids.tamPassoMUV.text)

        # quantidade de passos
        nPassos = len(self.picos)

        # calcula quantidade de passos e distância total
        distanciaTotal = nPassos * self.tamanhoPasso

        # calcula tempo médio de cada passo e tempo total
        tempoPasso = np.average(np.diff(muvTempo[self.picos]))
        tempoTotal = nPassos * tempoPasso

        # caso o usuário digite um valor para a velocidade inicial, pega esse valor.
        if(self.ids.velIniMUV.text != ""):
            self.veloIni = float(self.ids.velIniMUV.text)

        # cálculo da aceleração média (usando d = v0 * t + a * t ** 2 / 2)
        aceleracaoMedia = 2  * (distanciaTotal - self.veloIni * tempoTotal) / tempoTotal ** 2

        ind = np.arange(0, nPassos)

        # posições dos passos
        x = self.tamanhoPasso * ind
        # tempo dos passos
        t = tempoPasso * ind

        # posição inicial
        x0 = x[0]
        # tempo inicial
        t0 = t[0]
        # tempo final
        tf = t[-1]

        # obtém as posições e as velocidades estimadas pelo método de euler
        tEuler, xEuler, vEuler = euler(t0, tf, tempoPasso, x0, self.veloIni, aceleracaoMedia)

        # salva dados obtidos
        tempoMUV = tEuler[-1] - tEuler[0]
        distMUV = xEuler[-1] - xEuler[0]
        velocidadeMediaMUV = distMUV / tempoMUV
        paceMinsMUV, paceSegsMUV = kh2Pace(ms2kh(velocidadeMediaMUV))
        
        # ------- gráfico da velocidade -------

        # gera o gráfico da velocidade estimada pelo método de euler
        fig, ax = plt.subplots()
        plt.plot(tEuler, vEuler, "ro", label = "Estimado: Euler")
        plt.title(f"Velocidade no MUV")
        plt.xlabel("Tempo (s)")
        plt.ylabel("Velocidade estimada (m/s)")
        ax = plt.gca()
        ax.legend()
 
        # cria uma imagem com o gráfico e um widget com a imagem
        plt.savefig("MUVVel.png")
        wimg = Image(source = "MUVVel.png", allow_stretch = True, keep_ratio = True)
        wimg.reload()

        # apaga os widgets para o caso de já ter um gráfico e coloca o novo gráfico no lugar
        self.ids.dados.clear_widgets()
        self.ids.dados.add_widget(wimg)

        # ------- gráfico da posição -------

        # gera o gráfico da posição estimada pelo método de euler
        fig, ax = plt.subplots()
        plt.plot(tEuler, xEuler, "ro", label = "Estimado: Euler")
        plt.title(f"Posição no MUV")
        plt.xlabel("Tempo (s)")
        plt.ylabel("Posição estimada (m)")
        ax = plt.gca()
        ax.legend()

        # cria uma imagem com o gráfico e um widget com a imagem
        plt.savefig("MUVPosi.png")
        wimg = Image(source = "MUVPosi.png", allow_stretch = True, keep_ratio = True)
        wimg.reload()

        # coloca o gráfico no lugar
        self.ids.dados.add_widget(wimg)
        
        # ------- dados gerais obtidos ------

        textBox = BoxLayout(size_hint_y = 0.5, orientation = "vertical")
        lText1 = Label(text="Sumário de dados do experimento:", font_size = 24, text_size = self.size, halign = "center", valign = "center")
        lPosi = Label(text = f"Distância percorrida (m): {round(distMUV, 2)}", font_size = 24, text_size = self.size, halign = "left", valign = "center", pos_hint = {"x": 0.1})
        lTempo = Label(text = f"Tempo transcorrido (s): {round(tempoMUV, 1)}", font_size = 24, text_size = self.size, halign = "left", valign = "center", pos_hint = {"x": 0.1})
        lVelo = Label(text = f"Velocidade média no MUV (m/s):  {round(velocidadeMediaMUV, 2)}", font_size = 24, text_size = self.size, halign = "left", valign = "center", pos_hint = {"x": 0.1})
        lPassos = Label(text = f"Número de passos: {nPassos}", font_size = 24, text_size = self.size, halign = "left", valign = "center", pos_hint = {"x": 0.1})
        lPace = Label(text = f"Pace médio no MUV (min/km): {str(paceMinsMUV)} min {paceSegsMUV} s por km", font_size = 24, text_size = self.size, halign = "left", valign = "center", pos_hint = {"x": 0.1})

        textBox.clear_widgets()
        textBox.add_widget(lText1)
        textBox.add_widget(lPosi)
        textBox.add_widget(lTempo)
        textBox.add_widget(lVelo)
        textBox.add_widget(lPassos)
        textBox.add_widget(lPace)

        self.ids.dados.add_widget(textBox)

class MainApp(App):
    aceleracao = []
    tempo = []
 
    def build(self):
        return TelaPrincipal()
    
if __name__ == "__main__":
    MainApp().run()
