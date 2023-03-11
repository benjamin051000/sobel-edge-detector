img = imread("image.jpg");
gray = rgb2gray(img);
resized_gray = imresize(gray, [25, 25]);
writematrix(resized_gray, 'input.txt', 'Delimiter', 'tab');
