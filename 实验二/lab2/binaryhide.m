function [result,count,availabler,availablec]=binaryhide(cover,msg,goalfile,key,R0,R1,lumda)
%将文本文件转为二进制序列
frr=fopen(msg,'r');
[msg,count]=fread(frr,'ubit1');
fclose(frr);
%读入图像矩阵
images=imread(cover);
image=round(double(images)/255);  %四舍五入取整
%确定图像块的首地址
[m,n]=size(image);
m=floor(m/10);  %向负无穷大取整
n=floor(n/10);
temp=zeros([m,n]);
[row,col]=hashreplacement(temp,m*n,m,key,n);  %将m，n也作为密钥简化输入
%将块的坐标转换为块首像素地址
for i=1:m*n
    if row(i)~=1
        row(i)=(row(i)-1)*10+1;
    end
    if col(i)~=1
        col(i)=(col(i)-1)*10+1;
    end
end
%随机置乱8*8个点
temp=zeros(8);
[randr,randc]=hashreplacement(temp,64,key,m,n);  %将m，n也作为密钥简化输入
%分析可用的图像块
[availabler,availablec,image]=available(msg,count,row,col,m,n,image,R1,R0,lumda,randr,randc);
%信息嵌入
for i=1:count
    p1bi=computep1bi(availabler(i),availablec(i),image);
    if msg(i,1)==1
        if p1bi<R1
            image=editp1bi(availabler(i),availablec(i),image,0,R1-p1bi+1,randr,randc);%使p1(Bi)>R1
        elseif p1bi>R1+lumda
            image=editp1bi(availabler(i),availablec(i),image,1,p1bi-R1-lumda+1,randr,randc);%使p1(Bi)<R1+lumda
        else
        end
    end
    if msg(i,1)==0
        if p1bi>R0
            image=editp1bi(availabler(i),availablec(i),image,1,p1bi-R0+1,randr,randc);%使p1(Bi)<R0
        elseif p1bi<R0-lumda
            image=editp1bi(availabler(i),availablec(i),image,0,R0-lumda-p1bi+1,randr,randc);%使p1(Bi)>R0-lumda
        else
        end
    end
end
%信息写回保存
image=round(image);%防止边界扩散后的取整还原
result=image;
imwrite(result,goalfile);
subplot(2,1,1),imshow(images),title('原始图像');
subplot(2,1,2),imshow(result),title(['取阈值R0，R1为',int2str(R0),'，',int2str(R1),'以健壮参数lumda为',int2str(lumda),'下的信息',int2str(count),'bits隐秘效果']);