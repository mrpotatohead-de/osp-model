library(languageR)
library(lme4)       # for lmer()

rm(list=ls())      # clear all variables in memory


data_reading_aloud <- readRDS('Simulation1_data_reading_aloud.rds')
data_written_word_comprehension <- readRDS('Simulation1_data_written_word_comprehension.rds')

#For reading aloud test
data <- data_reading_aloud

#For written word comprehension test
#data <- data_written_word_comprehension

m1 <- glmer(correct ~ (1|item)+(1|version) + logtime + oral, data=data, family=binomial,
            control = glmerControl(optimizer ="bobyqa", optCtrl=list(maxfun=2e5)))
print(summary(m1))

m2 <- glmer(correct ~ (1|item)+(1|version) + logtime + focus, data=data, family=binomial)
print(summary(m2))

m3 <- glmer(correct ~ (1|item)+(1|version) + focus + logtime + oral, data=data, family=binomial,
            control = glmerControl(optimizer ="bobyqa", optCtrl=list(maxfun=2e5)))
print(summary(m3))

m4 <- glmer(correct ~ (1|item)+(1|version)+logtime+focus+oral+focus:oral, data=data, family=binomial,
            control = glmerControl(optimizer ="bobyqa", optCtrl=list(maxfun=2e5)))
print(summary(m4))

#For the training focus effect
anova(m1, m3)

#For the oral training effect
anova(m2, m3)

#Examine interaction between focus and pretrain
anova(m3, m4)


