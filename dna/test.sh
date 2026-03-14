for i in {1..4}; do
    python3 dna.py databases/small.csv sequences/${i}.txt
done
for i in {5..20}; do
    python3 dna.py databases/large.csv sequences/${i}.txt
done