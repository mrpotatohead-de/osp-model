
function out_result=examine_semantic_output(inputfile)

%%%load semantic vectors for all of the words
load 6ksem.mat
dict=importdata('6kdict', '');
[word,rem]=cellfun(@strtok, dict, 'UniformOutput', false);

%%%read the semantic activation file generated from evaluator
s_out=importdata(inputfile);
[token_sout,rem]=cellfun(@strtok, s_out, 'UniformOutput', false);
[item,rem]=cellfun(@strtok, rem, 'UniformOutput', false);
[test_word,activations]=cellfun(@strtok, rem, 'UniformOutput', false);
[C, IA, IB]=intersect(test_word, word);


%%%calculate the nearest distance between the input word and all of the
%%%words in the semantic space
nearest_dist=[];act_dist=[];nearest_tar=cell(size(s_out,1),1);
correct=[];out_result=cell(size(s_out,1),4);
for m=1:1:size(s_out,1)
    activation=str2num(char(activations(m,:)));
    dist_act_tar=sum((repmat(activation, size(s_out,1),1)-semantic_vector).^2,2);
    [nearest_dist(m),id]=min(dist_act_tar);
    nearest_tar(m)=test_word(id);
    act_dist(m)=dist_act_tar(m);
    correct(m)=strcmp(nearest_tar(m), test_word(m));
    out_result(m,:)=[test_word(m) nearest_tar(m) act_dist(m) correct(m)];
end
T=cell2table(out_result, 'VariableNames', {'Word', 'Semantic_Output', 'Error_Score', 'Correct'});
writetable(T,['nearest_' inputfile],'Delimiter', 'tab');

end