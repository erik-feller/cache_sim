%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 
% Script to parse through trace output and then make some graphs
% Erik Feller & Bryan DiLaura
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

files = dir;
data = {}
for i = 3:size(files,1)
    content = fileread(files(i).name);
    content = regexp(content, '\n', 'split');
    for j = 1:size(content,2)
        line = content(:,j);
        regexp(line, 'Memory')
    end
        
end