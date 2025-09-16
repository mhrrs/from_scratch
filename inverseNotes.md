# LOG:

ALGORITHM FOR LU:
step 1: elim for 1st column
- obtain pivot for first column -> pivot = [1,1]
- obtain multipliers by dividing the row values underneath the pivot by the pivot -> [n,1]/[1,1]
- obtain the K values (these are the multipliers * the row values of the pivot_row starting at the pivot column index)
- update U by subtracting by K for each equivalent index beyond the row of the pivot_row
- update L


* FUTURE STEPS FOR IMPROVEMENT: *
- remove the K values. just immediately index the multipliers with the operation. this requires less memory. 
- - Does this require more calling though? hmmm
- create compression of L&U into one matrix to conserve space? who knows, need to explore if this makes sense