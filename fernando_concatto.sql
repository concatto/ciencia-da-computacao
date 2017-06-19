--1
SELECT descricao FROM produto WHERE descricao LIKE 'Bo%';

--2
SELECT descricao FROM produto WHERE descricao LIKE '%nis%';

--3
SELECT descricao FROM produto WHERE descricao LIKE '_____de%';

--4
SELECT nome FROM cliente WHERE nome LIKE '_r___';

--5
SELECT descricao, preco_venda FROM produto WHERE preco_venda BETWEEN 50 AND 180;

--6
SELECT descricao,
	CASE WHEN qtd_estoque >= qtd_estoque_minimo
		THEN 'Estoque suficiente'
		ELSE 'Estoque insuficiente'
	END AS estoque 
FROM produto;

--7
SELECT CEIL(COUNT(id) / 3.0) AS paginas FROM produto;

--8
SELECT descricao FROM produto ORDER BY descricao LIMIT 3;

--9
SELECT descricao FROM produto ORDER BY descricao LIMIT 3 OFFSET 6;

--10: Igual ao exercício 9

--11
CREATE VIEW relatorio_de_vendas_mensal AS
	SELECT 
		COALESCE(SUM(preco_total), 0) AS total_vendas,
		COALESCE(AVG(preco_total), 0) AS media_vendas,
		COUNT(id) AS qtd_vendas,
		to_char(s, 'TMMonth') AS mes
	FROM (SELECT generate_series('2000-01-01', '2000-12-01', '1 month'::interval)::date AS s) s
	FULL OUTER JOIN venda
	ON extract('month' from s) = extract('month' from data)
	GROUP BY s ORDER BY s
;

--12
CREATE VIEW relatorio_de_vendas_mensal_cliente AS
	SELECT
		cliente.nome,
		to_char(data, 'TMMonth') AS mes,
		COUNT(venda.id) AS qtd_vendas,
		SUM(preco_total) AS total_vendas
	FROM venda
	INNER JOIN cliente ON cliente.id = venda.id_cliente
	GROUP BY cliente.nome, mes ORDER BY cliente.nome
;