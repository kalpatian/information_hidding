[count,msg,data]=hidedctadv('108.jpg','108_hide.jpg','1.txt',1982,1,0.1);
tt=extractdctadv('108_hide_JPEG_100.bmp','JPEG_100_result.txt',1982,304,0.1);
mistake = 0;
for i = 1:304
    if msg(i,1) ~= tt(i,1)
        mistake = mistake+1 ;
    end
end

disp(mistake);
rating = mistake/304;
disp(rating);