using JuMP
using HiGHS

mutable struct ColoringData
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

    return ColoringData(n, ng)
end

model = Model(HiGHS.Optimizer)

set_silent(model)

file = open(ARGS[1], "r")

data = readData(file)

@variable(model, x[i=1:data.n, j=1:data.n], Bin)
@variable(model, c[i=1:data.n], Bin)

for i=1:data.n
    @constraint(model, sum(x[i, j] for j=1:data.n) == 1)
end

for i=1:data.n
    for j=i:data.n
        if j in data.ng[i]
            for k=1:data.n
                @constraint(model, x[i,k] + x[j,k] <= 1)
            end
        end
    end
end

for i=1:data.n
    for j=1:data.n
        @constraint(model, x[i,j] <= c[j])
    end
end

@objective(model, Min, sum(c[i] for i=1:data.n))

optimize!(model)

sol = objective_value(model)

println("TP1 2021037902 = ", sol)