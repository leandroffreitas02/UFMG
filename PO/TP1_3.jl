using JuMP
using HiGHS

mutable struct CliqueData
    n::Int #numero de vertices
    ng::Array{Array{Int}} #vizinhanças de G
end

function readData(file)
    n = 0
    ng = [[]]

    for l in eachline(file)
        q = split(l, "\t")

        if q[1] == "n"
            n = parse(Int64, q[2])
            ng = [[] for i=1:n]
        
        elseif q[1] == "e"
            v = parse(Int64, q[2])
            u = parse(Int64, q[3])
            push!(ng[v], u)
            push!(ng[u], v)
        end
    end

    return CliqueData(n, ng)
end

model = Model(HiGHS.Optimizer)

set_silent(model)

file = open(ARGS[1], "r")

data = readData(file)

@variable(model, x[i=1:data.n], Bin)

for i=1:data.n
    for j=i:data.n
        if !(j in data.ng[i]) && (i != j)
            @constraint(model, x[i] + x[j] <= 1)
        end
    end
end

@objective(model, Max, sum(x[i] for i=1:data.n))

optimize!(model)

sol = objective_value(model)

println("TP1 2021037902 = ", sol)