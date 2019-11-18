function [] = Experiment1(im,degree)
im = imread(im);

a = degree / 180 * pi;
R = [cos(a), -sin(a); sin(a), cos(a)];
sz = size(im);
h = sz(1);
w = sz(2);
ch = sz(3);                         %通道数
c = [h; w] / 2;
im2 = uint8(zeros(h, w, 3));        %初始化旋转后的图片
im3 = uint8(zeros(h, w, 3));
im4 = uint8(ones(h, w, 3));
im9 = uint8(ones(h, w, 3));
for k = 1:ch
    for i = 1:h
       for j = 1:w
          p = [i; j];
          im4(i,j,k) = im(i,j,k);
          % round为四舍五入
          pp = round(R*(p-c)+c);
          if (pp(1) >= 1 && pp(1) <= h && pp(2) >= 1 && pp(2) <= w)
            im2(pp(1), pp(2), k) = im(i, j, k);
          end
          if (i >= j)
              im3(i,j,k) = im(i,j,k);
          end
          
          if (i >=150 && i<=300 && j>=150 && j<=300)
              im4(i,j,k) = 255;
              im9(i,j,k) = im(i,j,k);
          end
       end
    end
end
figure;
img5 = imrotate(im,90);
img6 = imrotate(im,180);
img7 = imrotate(im,270);
img8 = imrotate(im,0);

subplot(331),imshow(im2);
subplot(332),imshow(im3);
subplot(333),imshow(im4);
subplot(334),imshow(img5);
subplot(335),imshow(img6);
subplot(336),imshow(img7);
subplot(337),imshow(img8);
subplot(338),imshow(im9);
subplot(339),imshow(im);