function [result,count,availabler,availablec] = binaryhide(cover,msg,goalfile,key,R0,R1,lumda)
frr = fopen(msg,'r');
[msg,count] = fread(frr,'ubit1');
fclose(frr);
images = imread(cover);
images = im2bw(images);
% imshow(images);

image = round(double(images)/255);
[m,n] = size(image);
m = floor(m/10);
n = floor(n/10);
temp = zeros([m,n]);
[row,col] = hashreplacement(temp,m*n,m,key,n);
for i=1 : m*n
    if row(i) ~= 1
        row(i) = (row(i)-1)*10+1;
    end
    if col(i) ~= 1
        col(i) = (col(i)-1)*10+1;
    end
end
temp = zeros(8);
[randr,randc] = hashreplacement(temp,64,key,m,n);
[availabler,availablec,image] = available(msg,count,row,col,m,n,image,R1,R0,lumda,randr,randc);
for i=1 : count
    p1bi = computep1bi(availabler(i),availablec(i),image);
    if msg(i,1) == 1
        if p1bi<R1
            image = editp1bi(availabler(i),availablec(i),image,0,R1-p1bi+1,randr,randc);
        elseif p1bi>R1+lumda
            image = editp1bi(availabler(i),availablec(i),image,1,p1bi-R1-lumda+1,randr,randc);
        else
        end
    end
    if msg(i,1) == 0
        if p1bi>R0
            image = editp1bi(availabler(i),availablec(i),image,1,p1bi-R0+1,randr,randc);
        elseif p1bi<R0-lumda
            image = editp1bi(availabler(i),availablec(i),image,0,R0-lumda-p1bi+1,randr,randc);
        else
        end
    end
end
image = round(image);
result = image;
imwrite(result,goalfile);
subplot(121),imshow(images),title('原始图像');
subplot(122),imshow(result),title(['取阙值R0,R1为',int2str(R0),',',int2str(R1),'以及健壮参数 入 为',int2str(lumda),'下的信息',int2str(count),'bits隐秘效果']);
