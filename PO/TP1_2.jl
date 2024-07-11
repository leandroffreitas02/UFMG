using JuMP
using HiGHS

mutable struct LotsizingData
    n::Int #numero de períodos
    c::Array{Float64} #custo de produção
    d::Array{Float64} #demandas dos clientes
    s::Array{Float64} #custo de estoque
    p::Array{Float64} #multa do periodo
end

function readData(file)
    n = 0
    c::Array{Float64} = []
    d::Array{Float64} = []
    s::Array{Float64} = []
    p::Array{Float64} = []

    for l in eachline(file)
        q = split(l, "\t")
        num = parse(Int64, q[2])

        if q[1] == "n"
            n = num
            c = [0 for i=1:n]
            d = [0 for i=1:n]
            s = [0 for i=1:n]
            p = [0 for i=1:n]

        elseif q[1] == "c"
            c[num] = parse(Float64, q[3])

        elseif q[1] == "d"
            d[num] = parse(Float64, q[3])

        elseif q[1] == "s"
            s[num] = parse(Float64, q[3])
        
        elseif q[1] == "p"
            p[num] = parse(Float64, q[3])
        end
    end
    return LotsizingData(n, c, d, s, p)

end

model = Model(HiGHS.Optimizer)

set_silent(model)

file = open(ARGS[1], "r")

data = readData(file)

@variable(model, x[i=1:data.n] >= 0, Int)
@variable(model, y[i=1:data.n] >= 0, Int)
@variable(model, z[i=1:data.n] >= 0, Int)

@constraint(model, y[1] - z[1] == x[1] - data.d[1])

for i=2:data.n
    @constraint(model, y[i] - z[i] == y[i-1] - z[i-1] + x[i] - data.d[i])
end

@constraint(model, y[data.n] == z[data.n] - z[data.n-1])

@objective(model, Min, sum(x[i]*data.c[i] + y[i]*data.s[i] + z[i]*data.p[i] for i=1:data.n))

optimize!(model)

sol = objective_value(model)

println("TP1 2021037902 = ", sol)