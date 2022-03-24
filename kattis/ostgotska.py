A = input().split(" ")
print("dae ae ju traeligt va" if len([s for s in A if "ae" in s]) / len(A) >= 0.4 else "haer talar vi rikssvenska")