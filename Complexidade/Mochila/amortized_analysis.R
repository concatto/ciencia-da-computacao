files = c("experiments.csv", "experiments2.csv")
strategies = c("Sequencial", "Aleatório")

index <- 2

experiments <- read.csv(paste("~/ciencia-da-computacao/Complexidade/", files[index], sep=""))
experiments <- experiments[order(experiments$items),]

replications <- max(experiments$replication)
x <- unique(experiments$items)
y <- colMeans(matrix(experiments$elapsed_time, nrow = replications * 3))

polyModel <- lm(log(y)~log(x))
expModel <- lm(log(y)~x)

predictPoly = function(input) {
  return(exp(polyModel$coefficients[1]) * input^polyModel$coefficients[2])
}

predictExp = function(input) {
  return(exp(expModel$coefficients[1]) * exp(input * expModel$coefficients[2]))
}

plot(experiments$items, experiments$elapsed_time, xlab="Número de itens", ylab="Tempo (s)")
title(paste("Tempo de execução vs número de itens", strategies[index], sep=" - "))
curve(predictPoly, from=min(experiments$items), to=max(experiments$items), add=TRUE, col="forestgreen", lwd=3)
curve(predictExp, from=min(experiments$items), to=max(experiments$items), add=TRUE, col="goldenrod", lwd=3)
legend("topleft", c("Polinomial", "Exponencial"), col=c("forestgreen", "goldenrod"), lty=1, inset=c(0.02, 0.035), lwd=2, title="Hipótese")

print("Hipótese polinomial")
print(polyModel)
summary(polyModel)
print("Hipótese exponencial")
print(expModel)
summary(expModel)