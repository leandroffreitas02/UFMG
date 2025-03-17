#Malha no intervalo [0,1]
malha_x = np.linspace(0, 1, num=M + 1)# Malha horizontal com M+1 pontos
# Tamanho da figura e janelas
figsize = (12, 10)
fig, ax = plt.subplots(figsize=figsize)
fig.suptitle('Aproximação da solução pelo Método das Linhas')
ax.set_ylabel('Temperatura')
ax.set_xlabel('x')
ax.set_xlim((0,1))
ax.set_ylim((0,1))
sol_MOL = u_mlinhas(M, T, N, f)
for j in range(N+1):
    ax.plot(malha_x, sol_MOL[:,j], color='C'+str(j))
ax.grid(True)