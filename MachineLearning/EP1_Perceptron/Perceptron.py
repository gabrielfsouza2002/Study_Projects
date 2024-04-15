import numpy as np
import pandas as pd 
import matplotlib.pyplot as plt 

np.random.seed(66)

def Sinal(t):
    if t >= 0:
        return 1
    return 0

def predicao(X, W, b):
    return Sinal((np.matmul(X,W)+b)[0])

dados = pd.read_csv("Data.csv")
# Dados criados (linearmente separáveis)

X = np.array(dados[['RendaMensal','GastoComOutrasFinanciadoras']].copy())
y = np.array(dados['Aprovacao'].copy())
# Os critérios usados para ilustrar a aprovação de emprestivo são a Renda Mensal e o pagamento com outras financiadoreas. Os dados foram normalizados para realizamos os calculos.

def perceptron(X, y, W, b, learn_rate = 0.01):

  for i in range(len(X)):
    pred = predicao(X[i],W,b)
    if (pred-y[i]) < 0:
      for k in range(len(X[0])):
            W[k] = W[k] + (learn_rate*X[i][k])
            b = b + learn_rate
    elif (pred- y[i]) > 0:
      for k in range(len(X[0])):
            W[k] = W[k] - (learn_rate*X[i][k])
            b = b - learn_rate

  return W, b

def treinar(X, y, learn_rate = 0.01, num_epochs = 25):
  x_max = max(X.T[0])
  W = np.array(np.random.rand(2,1))
  b = np.random.rand(1)[0] + x_max

  vetor_retas = []
  for i in range(num_epochs):
    W, b = perceptron(X, y, W, b, learn_rate)
    
    coeficiente_angular = -W[0]/W[1]
    coeficiente_linear = -b/W[len(X[0])-1]
    vetor_retas.append((coeficiente_angular, coeficiente_linear ))

  return vetor_retas



vetor_retas = treinar(X,y)
i = np.array(dados['RendaMensal'])
j = np.array(dados['GastoComOutrasFinanciadoras'])
df = pd.DataFrame({"Status": y})

def cor_do_ponto(valor: int) -> str:
    """Retorna a cor de um ponto do gráfico, de acordo com o seu valor."""
    if valor == 0:
        return "red"
    else:
        return "green"

df['Color'] = df['Status'].apply(cor_do_ponto)

for k in range(len(vetor_retas)):
  plt.scatter(i, j, c=df['Color'])
  plt.xlabel("Salário Mensal")
  plt.ylabel("Dívida com outras Financiadoras")
  plt.title("Perceptron Model") 
  y = vetor_retas[k][0]*i + vetor_retas[k][1]
  plt.plot(i,y)
  print("\n Epoca : ",k+1)
  plt.show()
  
# Vermelho = crédito não aprovado
# Verde = crédito aprovado