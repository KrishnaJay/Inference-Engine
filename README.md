# Inference-Engine

Prove or disprove the given query based on the knowledge base

Project description

After the high-profile lawsuit in which you succeeded to bring RealityMan to justice after proving that
distributing his Nintendo emulator was a criminal act, everyone wants to hire you! From disputes over tech
patents, to lawsuits on questions of privacy in social media, to suits on liability issues with self-driving cars, to
disputes between Hollywood celebrities and their agents or producers, you are just running out of time and
energy to run all these cases by hand like we have done in the lectures.
Because of the highly sensitive nature of the cases you handle, and because of the extremely high monetary
amounts involved, you cannot trust any existing. You thus decide to create your own, ultra-optimized
inference engine.
After much debating, you decide that the knowledge bases which you will create to handle each case will
contain sentences with the following defined operators:
NOT X ~X
X OR Y X | Y
Your assignment is:
You will use first-order logic resolution to solve this problem.
Format for input.txt:
<NQ = NUMBER OF QUERIES>
<QUERY 1>
…
<QUERY NQ>
<NS = NUMBER OF GIVEN SENTENCES IN THE KNOWLEDGE BASE>
<SENTENCE 1>
…
<SENTENCE NS>
where
• Each query will be a single literal of the form Predicate(Constant) or ~Predicate(Constant).
• Variables are all single lowercase letters.
• All predicates (such as Sibling) and constants (such as John) are case-sensitive alphabetical strings that
begin with an uppercase letter.
• Each predicate takes at least one argument. Predicates will take at most 100 arguments. A given
predicate name will not appear with different number of arguments.
• There will be at most 100 queries and 1000 sentences in the knowledge base.
• See the sample input below for spacing patterns.
• You can assume that the input format is exactly as it is described. There will be no syntax errors in the
given input.
Format for output.txt:

For each query, determine if that query can be inferred from the knowledge base or not, one query per line:
<ANSWER 1>
…
<ANSWER NQ>
where
each answer should be either TRUE if you can prove that the corresponding query sentence is true given the
knowledge base, or FALSE if you cannot.
