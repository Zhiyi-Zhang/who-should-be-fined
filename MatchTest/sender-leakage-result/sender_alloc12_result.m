function sender_alloc12_result(name1)
input = textread(name1,'','delimiter',' ','emptyvalue',NaN);
input = input(:,[3 5]);
a = input(1:6,:);
sz= size(a);
for i=1:sz(1)
    a(i,2) = 1 - a(i,2);
    if a(i,2)<1e-12
        a(i,2) = 1e-12;
    end
end
a(:,2) = a(:,2) .* 100

figure
h1=axes;

%------------------------figure3(c)
%%输入数据
X1=[];
Y1=[];
X2=[];
Y2=[];

%%输入数据
%-----------------------
plot(a(:,1),a(:,2),'linewidth',5.0,'Color',[0.274509817361832 0.560784339904785 0.823529422283173])
hold on


my_yticks = [1e-10 1e-8 1e-6 1e-4 1e-2 1 10 100];
my_ylabels = {'<10^{-10}','10^{-8}','10^{-6}','10^{-4}','10^{-2}','1','10','100'};

l = 1;
r = 8;
for j=1:8
    i=9-j;
    tmp = min([min(a(:,2))]);
    if tmp>my_yticks(i)
        l = i;
        break;
    end
end

for i=1:8
    tmp = max([max(a(:,2))]);
    if tmp<my_yticks(i)
        r = i;
        break;
    end
end

my_yticks = my_yticks(l:r);
my_ylabels = my_ylabels(l:r);

xlabel('Unique Size', 'FontSize',20)
ylabel('Failure Ratio (%)', 'FontSize',20)
%xticks([1 2 5 10 50 100])
%xticklabels({'1','2','5','10','50','100'})
yticks(my_yticks)
yticklabels(my_ylabels)
%set(gca, 'XScale', 'log')
set(gca, 'YScale', 'log')
set(gca,'FontSize',20);
set(gca,'box','off');
set(gca,'linewidth',1.5);
set(gcf,'color',[1 1 1])
h2=legend;
set(h2,'box','off')

Position=h1.Position;
eff=-0.05;
annotation('arrow',[Position(1) Position(1)],[Position(2)+eff+0.05 Position(2)+Position(4)+eff+0.07],'linewidth',3);
annotation('arrow',[Position(1) Position(1)+Position(3)+0.01],[Position(2)+eff+0.05 Position(2)+eff+0.05],'linewidth',3);
hgexport(gcf,[name1,'12.eps']);
end