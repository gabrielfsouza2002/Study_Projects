#Aluno: Gabriel Ferreira de Souza Araujp
#NUSP: 12718100

# Referencias: https://www.youtube.com/watch?v=kaL-j412a5A&ab_channel=UNIVESP

####################################################################################################
import numpy as np

# Conjunto de pontos (x,y)
x = [-1,0,1,2]
y = [1,-1,2,3]

grau=1
lista_erro = []
numero_grau = int(input("Insira até qual grau deseja testar para obter o melhor ajuste.\nOBS: Os pontos de ajuste podem ser modificados no programa manualmente e o melhor grau de ajuste está informado no final da saída do programa."))

while grau <= numero_grau:
    
    # Gerar matriz (m) para ajuste polinomial para cada grau
    list_erro = []
    m = np.zeros(shape=(grau+1,grau+1))
    p=0
    for i in range (len(m)):
        n=p
        for j in range (len(m)):
            list=[]
            for k in x:
                list.append(k**n)
            soma = np.sum(list)
            m[i][j] = soma
            n += 1
        p+=1
        
    print("=========================================================================================================================")
    print("Matriz para grau",grau,":\n",m)  
    print("")
     
    # Gerar vetor Y para cada grau
    Y  = [0] * (grau+1)
 
    
    for l in range (len(Y)):
        
        Ylist = []
        for k in range (len(x)):
            Ylist.append((x[k]**l) * y[k])
        Ysoma = np.sum(Ylist)
        Y[l] = Ysoma
    
    print("Vetor Y para grau",grau,":\n",Y)
    print("")
    
    # Gerar vetor v* (resolução) para cada grau
    v = np.linalg.solve(m,Y)
    
    print("Vetor v* (resposta) para grau",grau,":\n",v)
    
    # Obter erro quadrático médio para cada grau
    for i in x:
        n=0
        p=0
        for j in v:
            g = j*(i**n)
            p = p + g 
            n += 1
            erro = p
        list_erro.append(erro)
       

        
    erro_quadratico_medio = np.square(np.subtract(y,list_erro)).mean()
    

    print("")
    print("Erro quadrático médio para grau",grau,":\n",erro_quadratico_medio)
    
    lista_erro.append(erro_quadratico_medio)
   
   
    #Identificar o melhor ajuste verificando qual é o menor erro quadrático médio para cada grau
    if grau >= numero_grau:
        n=0
        while n < grau:
            if lista_erro[n] == min(lista_erro):
                print("")
                print("=========================================================================================================================")
                print("                             O melhor ajuste para o conjuto de pontos é para grau =",n+1)
            n+=1

    grau = grau + 1
    