function result = Experiment2_get(output,len_total,goalfile)
ste_cover = imread(output);
show2 = ste_cover(:,:,1);
ste_cover = double(ste_cover);
show = ste_cover(:,:,1);

[m,n] = size(ste_cover);
frr = fopen(goalfile,'a');
 p = 1;
 for f2 = 1:n
     for f1 = 1:m
         if bitand(ste_cover(f1,f2,1),1) == 1
             fwrite(frr,1,'ubit1');
             result(p,1) = 1;
         else
             fwrite(frr,0,'ubit1');
             result(p,1) = 0;
         end
         if p == len_total
             break;
         end
         p = p+1;
     end
        if p == len_total
            break;
        end
 end
 fclose(frr);