# fillit

Fillit is designed to process specifically formatted input file that
includes a list of 1 to 26 tetriminos.
It then rearranges them into the smallest possible square.

As an example, running `./fillit example.fillit` results in following output:  
`AABCDDDDEF.`  
`AABCGGH.EFF`  
`.BBC.GH.EEF`  
`II.C.GHJJJL`  
`MIIKK.HJ..L`  
`MOPKKNNNNLL`  
`MOPPQQRR.TT`  
`MOOP.QURRTT`  
`SSSVVQUZXXX`  
`SWW.VUUZXYY`  
`..WWV.ZZ.YY`
  
To-do / things to improve in the future:
* move from symbol arrays into bitfields to improve operation speed
* use libft linked list-functions instead of custom ones
* optimization!
