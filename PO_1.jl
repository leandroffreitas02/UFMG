using JuMP
using HiGHS

mutable struct EmpacotamentoData
    n::Int #numero de objetos
    w::Array{Float64} #peso dos objetos
end

function readData(file)
    n = 0
    w::Array{Float64} = []

    for l in eachline(file)
        q = split(l, "\t")
        num = parse(Int64, q[2])

        if q[1] == "n"
            n = num
            w = [0 for i=1:n]

        elseif q[1] == "o"
            w[num+1]= parse(Float64, q[3])
        end
    end
    return EmpacotamentoData(n, w)
end

model = Model(HiGHS.Optimizer)

set_silent(model)

file = open(ARGS[1], "r")

data = readData(file)

@variable(model, c[i=1:data.n], Bin)
@variable(model, x[i=1:data.n, j=1:data.n], Bin)

for j=1:data.n
    @constraint(model, sum(x[i, j]*data.w[i] for i=1:data.n) <= c[j]*20)
end

for i=1:data.n
    @constraint(model, sum(x[i,j] for j=1:data.n) == 1)
end

@constraint(model, sum(c[i] for i=1:data.n) >= 1)

@objective(model, Min, sum(c[i] for i=1:data.n))

optimize!(model)

sol = objective_value(model)

println("TP1 2021037902 = ", sol)