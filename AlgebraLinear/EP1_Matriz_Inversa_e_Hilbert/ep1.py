#!/usr/bin/env python
# coding: utf-8

# In[168]:


import numpy as np
import math
import random
import sys

#NOME: GABRIEL FERREIRA DE SOUZA ARAUJO
#NUSP: 12718100 


def matriz_triangular_superior(m): #Cria uma matriz triangular superior aleatoria de ordem "m"
    lista =list()
    for i in range(1, m + 1):
        linha = list()
        for j in range(1, m + 1):
            if i > j:
                linha.append(0)
            else:
                while True:
                        f =random.randint(0,101)
                        if f < 50:
                            v = random.uniform(0 , 1000)
                        else:
                             v = random.randint(0 , 1000)
                        break
                linha.append(v)
        lista.append(linha)
    matriz = lista
    return matriz

def transposeMatrix(M): #Retorna matriz transpota
    aux=[]
    for j in range(len(M[0])):
        linha=[]
        for i in range(len(M)):
            linha.append(M[i][j])
        aux.append(linha)
    return aux

def matriz_triangular_inferior (m): #Cria uma matriz triangular inferior aleatoria de ordem "m"
    matriz = transposeMatrix(matriz_triangular_superior(m))
    return matriz

def gerar_matriz (n_linhas, n_colunas): #Retorna uma matriz ixj de zeros
    matriz = []
    for _ in range(n_linhas):
        matriz.append( [0] * n_colunas )
    return matriz

def delete(m,indice,axis) : #Deleta linha(axis=0) ou coluna(axis=1) da matriz (m)
    if (axis == 0):
        for i in range(len(m)):
            if (i==indice):
                del m[i]
                return m
    elif (axis == 1):
        for row in m:
            for i in reversed(range(len(row))):
                if i == indice:
                    del row[i:i+1]
    return m

def multiplica_matriz(a,b): #Retorna a a matriz produto de "a,b"
    nlin_a, ncol_a = len(a), len(a[0])
    nlin_b, ncol_b = len(b), len(b[0])
    assert ncol_a == nlin_b
    
    list = []
    for lin in range(nlin_a):
        list.append([])
        for col in range(ncol_b):
            list[lin].append(0)
            for k in range(ncol_a):
                list[lin][col] += a[lin][k] * b[k][col]
                
    #tratamento de erros
    for b in range(len(list)):
        for c in range (len(list)):
            error1 = 0.5
            error2 = 0.9999999999999999
            error3 = 1.03
            if(list[b][c] <= error1):
                list[b][c] = 0
            if(list[b][c] <= error2 and list[b][c] >= error2-error1 or (list[b][c] <= error3 and list[b][c] >= error2)):
                list[b][c] = 1.0
    return list

def matriz_igual(a,b): #Verifica se duas matrizes (a,b) são iguais
    nlin_a, ncol_a = len(a), len(a[0])
    nlin_b, ncol_b = len(b), len(b[0])
    if (nlin_a == nlin_b) and (ncol_a == ncol_b):
        for i in range(nlin_a):
            for j in range(ncol_a):
                if (a[i][j] != b[i][j]):
                    return False
        return True
    else:
        return False
    
def matriz_identidade(m): #Retorna a identidade da matriz "m"
    a = gerar_matriz(len(m),len(m))
    for i in range (len(a)):
        for j in range (len(a)):
            if(i==j):
                a[i][j] = 1.0
    return(a)
    
def matriz_inversa(m): #Retorna a inversa da matriz"m"
    n = len(m)
    a = gerar_matriz(n,2*n)
    
    for i in range(n):
        for j in range(n):
            a[i][j] = m[i][j]

    for i in range(n):        
        for j in range(n):
            if i == j:
                a[i][j+n] = 1

        for j in range(n):
            if i != j:
                ratio = a[j][i]/a[i][i]
                for k in range(2*n):
                    a[j][k] = a[j][k] - ratio * a[i][k]

    for i in range(n):
        divisor = a[i][i]
        for j in range(2*n):
            a[i][j] = a[i][j]/divisor

    cont = 0
    while (cont<len(a)):
        a = delete(a,0, 1)
        cont += 1
    return a

def matriz_de_hilbert(m): #Retorna matriz de Hilber de ordem "m"
    a = gerar_matriz(m,m)
    for i in range(len(a)):
        for j in range(len(a)):
            a[i][j] = 1/((i+1)+(j+1)-1)
    return a

def inversa_matriz_triangular_superior(m): #Retorna a inversa de uma matriz triangular superior aleatoria de ordem(m)
    matriz = matriz_inversa(matriz_triangular_superior(m))
    return np.array(matriz)

def inversa_matriz_triangular_inferior(m): #Retorna a inversa de uma matriz triangular inferior aleatoria de ordem(m)
    matriz = matriz_inversa(matriz_triangular_inferior(m))
    return np.array(matriz)

def teste_inversa_matriz_triangular_superior(quantidade_de_testes,tamanho_da_matriz):

    cont =0
    certo =0
    errado =0
    divsao_por_zero=0

    while (cont < quantidade_de_testes):
        try:
            matriz = matriz_triangular_superior(tamanho_da_matriz)
            ainv = matriz_inversa(matriz)
            identidade = matriz_identidade(matriz)
            multiplicacao = multiplica_matriz(matriz,ainv)
            cont += 0
            eh_igual = matriz_igual(identidade,multiplicacao)
            if(eh_igual):
                certo +=1
            else:
                errado +=1
                print(multiplicacao)

        except ZeroDivisionError:
            divsao_por_zero +=1
        cont +=1

    print("Sucessos:",certo)
    print("Fracassos:",errado)
    print("Divisões por Zero:",divsao_por_zero)


def teste_inversa_matriz_triangular_inferior(quantidade_de_testes,tamanho_da_matriz):

    cont =0
    certo =0
    errado =0
    divsao_por_zero=0

    while (cont < quantidade_de_testes):
        try:
            matriz = matriz_triangular_inferior(tamanho_da_matriz)
            ainv = matriz_inversa(matriz)
            identidade = matriz_identidade(matriz)
            multiplicacao = multiplica_matriz(matriz,ainv)
            cont += 0
            eh_igual = matriz_igual(identidade,multiplicacao)
            if(eh_igual):
                certo +=1
            else:
                errado +=1
                print(multiplicacao)

        except ZeroDivisionError:
            divsao_por_zero +=1
        cont +=1

    print("Sucessos:",certo)
    print("Fracassos:",errado)
    print("Divisões por Zero:",divsao_por_zero)
    

def teste_inversa_matriz_de_hilbert():
    
    cont = 1
    while (cont <= 50):
        matriz = matriz_de_hilbert(cont)
        ainv = matriz_inversa(matriz)
        identidade = np.array(matriz_identidade(matriz))
        multiplicacao = multiplica_matriz(matriz,ainv)
        eh_igual = matriz_igual(identidade,multiplicacao)
        if(eh_igual):
            print("PARA",cont,"DIMENSÕES, O TESTE FOI UM SUCESSO:")
        else:
            print("PARA",cont,"DIMENSÕES, O TESTE FOI UM FRACASSO:")
        cont +=1
        
def correcao():
     
    #QUESTAO_1 = inversa_matriz_triangular_superior(5)
    #QUESTAO_2 = inversa_matriz_triangular_inferior(5)
    #QUESTAO_3 = matriz_inversa(matriz_NxN)
    #QUESTAO_4 = teste_inversa_matriz_triangular_superior(10,50)
    #QUESTAO_5 = teste_inversa_matriz_triangular_inferior(10,50)
    #QUESTAO_6 = teste_inversa_matriz_de_hilbert()
    
    questao = int(input("Digite o número da questão da lista (de 1 a 6) que deseja visualizar: "))
    
    if (questao == 1):
        print("\nQUESTÃO 1: Descreva um algoritmo que calcula a inversa de uma matriz triangular superior.\n")
        return inversa_matriz_triangular_superior(5)
    elif (questao == 2):
        print("\nQUESTÃO 2: Descreva um algoritmo que calcula a inversa de uma matriz triangular inferior.\n")
        return inversa_matriz_triangular_inferior(5)
    elif (questao == 3):
        print("\nQUESTÃO 3: Descreva um algoritmo que calcula a inversa de uma matriz nxn.\n")
        matriz_NxN = [[3,2,1],[3,4,5],[5,3,2]]
        return matriz_inversa(matriz_NxN)
    elif (questao == 4):
        print("\nQUESTÃO 4: Implemente o algoritmo do item 1 e teste o seu código para a matrizes aleatórias. Analise o resultado dos seus testes.\n")
        return teste_inversa_matriz_triangular_superior(10,50)
    elif (questao == 5):
        print("\nQUESTÃO 5: Implemente o algoritmo do item 2 e teste o seu código para a matrizes aleatórias. Analise o resultado dos seus testes.\n")
        return teste_inversa_matriz_triangular_inferior(10,50)
    elif (questao == 6):
        print("\nQUESTAO 6: Implemente o algoritmo do item 3 e teste o seu código para a matriz de Hilbert de dimensões de 1 a 50. Analise os resultados dos seus testes.\n")
        return teste_inversa_matriz_de_hilbert()
    
correcao()



# In[ ]:




