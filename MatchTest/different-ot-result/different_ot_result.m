function different_ot_result(name1,name2,name3)
a = textread(name1,'','delimiter',',','emptyvalue',NaN);
b = textread(name2,'','delimiter',',','emptyvalue',NaN);
c = textread(name3,'','delimiter',',','emptyvalue',NaN);

sz= size(a)
before = [0.5 0.67 0.75];
after = [0.33 0.67 1];
a = check(a,before,after);
b = check(b,before,after);
c = check(c,before,after);
for i=1:sz(1)
    a(i,2) = 1-a(i,2);
    b(i,2) = 1-b(i,2);
    c(i,2) = 1-c(i,2);
    
    if a(i,2)<1e-16
        a(i,2) = 1e-16;
    end
    if b(i,2)<1e-16
        b(i,2) = 1e-16;
    end
    if c(i,2)<1e-16
        c(i,2) = 1e-16;
    end
end
a(:,2) = a(:,2) .* 100;
b(:,2) = b(:,2) .* 100;
c(:,2) = c(:,2) .* 100;

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

plot(b(:,1),b(:,2),'linewidth',5.0,'Color',[0.4 0.4 0.4])
hold on

plot(c(:,1),c(:,2),'linewidth',5.0,'Color',[0.87058824300766 0.490196079015732 0])
hold on

my_yticks = [1e-14 1e-12 1e-10 1e-8 1e-6 1e-4 1e-2 1 100];
my_ylabels = {'<10^{-14}','10^{-12}','10^{-10}','10^{-8}','10^{-6}','10^{-4}','10^{-2}','1','10^{2}'};

l = 1;
r = 9;
for j=1:9
    i=10-j;
    tmp = min([min(a(:,2)),min(b(:,2)),min(c(:,2))])
    if tmp>my_yticks(i)
        l = i;
        break;
    end
end

for i=1:9
    tmp = max([max(a(:,2)),max(b(:,2)),max(c(:,2))])
    if tmp<my_yticks(i)
        r = i;
        break;
    end
end

my_yticks = my_yticks(l:r);
my_ylabels = my_ylabels(l:r);

xlabel('OT settings', 'FontSize',20)
ylabel('Error rate (%)', 'FontSize',20)
xticks([0.33 0.67 1])
xticklabels({'1-2 OT','2-3 OT','3-4 OT'})
yticks(my_yticks)
yticklabels(my_ylabels)
set(gca, 'YScale', 'log')
set(gca,'FontSize',20);
set(gca,'box','off');
set(gca,'linewidth',1.5);
set(gcf,'color',[1 1 1])
legend('Location','northeast')
legend({'2 leakers out of 6 receivers','3 leakers out of 6 receivers','6 leakers out of 6 receivers'})
h2=legend;
set(h2,'box','off')

Position=h1.Position;
eff=-0.05;
annotation('arrow',[Position(1) Position(1)],[Position(2)+eff+0.05 Position(2)+Position(4)+eff+0.07],'linewidth',3);
annotation('arrow',[Position(1) Position(1)+Position(3)+0.01],[Position(2)+eff+0.05 Position(2)+eff+0.05],'linewidth',3);
hgexport(gcf,[name1,'_',name2,'_',name3,'.eps']);
end

function ret = check(input,before,after)
ret = input;
sz = size(input);
for i=1:sz(1)
    for j=1:3
        if input(i,1) == before(j)
            ret(i,1) = after(j);
        end
    end
end
end