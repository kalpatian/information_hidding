function[ ste_cover,len_total] = Experiment2_hide(input,file,output)
cover = imread(input);
ste_cover = cover;
ste_cover = double(ste_cover);
% show = ste_cover(:,:,1);

f_id = fopen(file,'r');
[msg,len_total] = fread(f_id,'ubit1');

[m,n] = size(ste_cover);
if len_total>m*n
    error('信息量过大，请更换图像');
end

p = 1;
for f2 = 1:n
    for f1 = 1:m
        ste_cover(f1,f2,1) = ste_cover(f1,f2,1) - mod(ste_cover(f1,f2,1),2) + msg(p,1);
        if p == len_total
            break;
        end
        p = p+1;
    end
    if p == len_total
        break;
    end
end
ste_cover = uint8(ste_cover);
%show2 = ste_cover(:,:,1);
imwrite(ste_cover,output);
subplot(121),imshow(cover);title('原始图像');
subplot(122),imshow(output);title('隐藏信息的图像');
