
function out_result=examine_semantic_output_awl(inputfile)

%%%load semantic vectors for all of the words
s=importdata('exp_jo_taylor_set1_meaning_in_6ksem.txt', '');
numFeature=2446;
semantic_vector=zeros(size(s,1),numFeature);
maxFeature=zeros(size(s,1),1);

for i=1:1:size(s,1)
    features=[];token=[];rem=[];
    [token, rem]=strtok(s(i,:));
    [token, rem]=strtok(rem);
    [token, rem]=strtok(rem);
    features=str2num(char(rem));
    tarWord(i)=token;
    maxFeature(i)=max(features)+1;
    semantic_vector(i,features+1)=1;
end

%%%read the semantic activation file generated from evaluator
s_out=importdata(inputfile);
[token_sout,rem]=cellfun(@strtok, s_out, 'UniformOutput', false);
[item,rem]=cellfun(@strtok, rem, 'UniformOutput', false);
[test_word,activations]=cellfun(@strtok, rem, 'UniformOutput', false);

%%%calculate the nearest distance between the input word and all of the
%%%words in the semantic space
nearest_dist=[];act_dist=[];nearest_tar=cell(size(s_out,1),1);
correct=[];out_result=cell(size(s_out,1),5);
for m=1:1:size(s_out,1)
    activation=str2num(char(activations(m,:)));
    dist_act_tar=sum((repmat(activation, size(s_out,1),1)-semantic_vector).^2,2);
    [nearest_dist(m),id]=min(dist_act_tar);
    nearest_tar(m)=test_word(id);
    act_dist(m)=dist_act_tar(m);
    correct(m)=strcmp(nearest_tar(m), test_word(m));
    out_result(m,:)=[item(m) test_word(m) nearest_tar(m) act_dist(m) correct(m)];
end
T=cell2table(out_result, 'VariableNames', {'Item' 'Word', 'Semantic_Output', 'Error_Score', 'Correct'});
writetable(T,['nearest_' inputfile],'Delimiter', 'tab');

end