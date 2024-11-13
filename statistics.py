import sys


stats = {}
for line in sys.stdin:
    line = line.strip()
    stats[line] = stats.get(line, 0) + 1
total = sum(stats.values())
for (key, value) in sorted(stats.items(), key=lambda p: p[1], reverse=True):
    print(f'{key:25} {value:10} {100 * value / total:10.2f}%')

