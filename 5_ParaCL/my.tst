fst = 0;
snd = 1;
iters = ?;
while (iters > 0)
{
    tmp = fst;
    fst = snd;
    snd = snd + tmp;
    iters = iters - 1;
}
print snd;