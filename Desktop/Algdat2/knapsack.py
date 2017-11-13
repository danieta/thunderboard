
def knapsack(n, W):
	w = [320, 301, 371, 296, 303, 359, 148, 275, 296, 395]
	v = [18, 27, 51, 36, 24, 22, 29, 10, 24, 40]

	#v = [12,10,20,15]
	#w = [2,1,3,2]

	K = [[0 for x in range(W+1)] for x in range(n+1)]

	for i in range(1,n+1):
		for j in range(W+1):
			x = K[i-1][j]
			if j < w[i-1]:
				K[i][j] = x
			else:
				y = K[i-1][j-w[i-1]] + v[i-1]
				K[i][j] = max(x,y)
	#for i in K:
		#print(i)
	return K[n][W]


def main():
	print(knapsack(10,740))


if __name__ == "__main__":
	main()