from collections import defaultdict


alpha_freq_map = defaultdict(int)
word_freq_map = defaultdict(int)

with open('raw_words.txt', 'r') as rfp:
    words = []
    for l in rfp.readlines():
        l = l.strip()
        words.append(l)
    for word in words:
        for c in word:
            alpha_freq_map[c] += 1
    for word in words:
        score = 0
        for c in word:
            score += alpha_freq_map[c]
        word_freq_map[word] = score
    
    with open('words.txt', 'w') as wfp:
        wfp.writelines(
            "\n".join(o[0] for o in reversed(sorted(word_freq_map.items(),
                                                    key=lambda o: o[1]))))