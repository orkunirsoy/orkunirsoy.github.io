---
layout: default
title: Research
subtitle: Publications, talks, current projects and past work.
redirect_from:
  - /Research&Teaching.html
---

## Current research

<div class="card">
  <h3>TANGCO: Learning Topology-Aware Capacity Allocation for Cascading Failures</h3>
  <p class="meta">PhD Research · 2026 · with Prof. Leman Akoglu and Prof. Osman Yağan · Accepted at ACM SIGKDD 2027</p>
  <p>A graph neural network policy trained with policy-gradient reinforcement learning through a cascade simulator to optimize capacity allocation against overload-driven cascading failures. It outperformed the best of four heuristic baselines on all 45 synthetic instances and 40 of 45 real-network conditions, with robustness gains of 1.6%–246%. Policies pretrained on synthetic networks transfer to unseen real-world networks, matching per-network training.</p>
  <div class="tags"><span>Graph neural networks</span><span>Reinforcement learning</span><span>PyTorch</span></div>
  <div class="pub-links"><a class="chip" href="https://arxiv.org/abs/2608.13212">arXiv</a></div>
</div>

<div class="card">
  <h3>XRP Ledger: Network Robustness and Cross-Currency Routing</h3>
  <p class="meta">2026–Present</p>
  <p>Edge-augmentation strategies to improve XRP Ledger network robustness, leading to a paper at IEEE GLOBECOM 2026. Currently evaluating the optimality gap of cross-currency pathfinding and developing scalable graph-based routing methods.</p>
  <div class="tags"><span>Graph algorithms</span><span>Routing</span><span>Robustness</span></div>
</div>

## Publications & manuscripts

{% include pub-list.html items=site.data.publications.papers %}

## Conference presentations

{% include pub-list.html items=site.data.publications.conferences %}

## Invited talks

{% include pub-list.html items=site.data.publications.talks %}

## Previous research experience

<div class="card">
  <h3>Cascading Failures in Multiplex Flow Networks</h3>
  <p class="meta">PhD Research · 2024–2026 · Advisor: Prof. Osman Yağan</p>
  <p>Mathematical and simulation models for overload-based cascades in multiplex networks with joint and partial functionality. We analyze robustness, optimal capacity allocation, and transition behavior. Published in IEEE TNSE, with follow-up work in the final editorial phase at Physical Review E.</p>
  <div class="tags"><span>Cascading failures</span><span>Network science</span><span>Optimization</span><span>Simulation</span></div>
</div>

<div class="card">
  <h3>Knight Fellow: Online Harm &amp; Community Dynamics</h3>
  <p class="meta">CMU IDEaS Center · Aug 2024 – Aug 2025</p>
  <p>Built cross-platform NLP and network-analysis pipelines (Reddit, Voat, Parler) using Transformer models to study conspiratorial discourse, sentiment, community evolution, and potential early-warning signals.</p>
  <div class="tags"><span>NLP</span><span>Transformers</span><span>Social networks</span></div>
</div>

<div class="card">
  <h3>Graduate Research Assistant</h3>
  <p class="meta">Socio-Economic System Dynamics Lab (SESDYN), Boğaziçi University · Sep 2020 – Aug 2023</p>
  <p>Modeled online misinformation diffusion for my master's thesis and contributed to published work on social mobilization (with the DiaPols group) and healthcare policy simulation (with the Karanfil Lab, Koç University).</p>
  <div class="tags"><span>System dynamics</span><span>Social network analysis</span><span>Policy analysis</span></div>
</div>

## Selected projects

<div class="card">
  <h3>Generative Diffusion for Flexible Job-Shop Scheduling</h3>
  <p class="meta">11-785 Introduction to Deep Learning · Carnegie Mellon University · Fall 2026</p>
  <p>Co-developed a heterogeneous GNN with a categorical diffusion model to generate optimal schedules for problem instances; led ideation, model training, and experimental design. Non-delay decoding reduced makespan gaps by about 50% in team experiments.</p>
  <div class="tags"><span>Diffusion models</span><span>GNNs</span><span>PyTorch</span></div>
</div>

<div class="card">
  <h3>Computer Vision &amp; Sequence Modeling</h3>
  <p class="meta">11-785 Introduction to Deep Learning · Carnegie Mellon University · Fall 2026</p>
  <p>Trained CNNs from scratch for face classification and verification across different architectures; implemented RNN, GRU, CTC, and attention components and trained a Transformer for voice-to-text speech recognition.</p>
  <div class="tags"><span>CNNs</span><span>RNNs</span><span>Transformers</span></div>
</div>

<div class="card">
  <h3>Research-Paper RAG &amp; Few-Shot LLM Evaluation</h3>
  <p class="meta">17-630 Prompt Engineering · Carnegie Mellon University · Summer 2026</p>
  <p>Built a 26-document question-answering pipeline with ChromaDB, comparing indexing strategies and improving BERTScore F1 from 0.572 to 0.683. Compared demonstration selection and ordering for multi-label classification with Llama and GPT models, using held-out F1 to test generalization.</p>
  <div class="tags"><span>RAG</span><span>ChromaDB</span><span>LLMs</span></div>
</div>

<div class="card">
  <h3>Chain-of-Thought Sentiment Classification</h3>
  <p class="meta">10-701 Introduction to Machine Learning (PhD) · Carnegie Mellon University</p>
  <p>Applied THOR-based multi-hop reasoning to Yelp Reviews using Flan-T5 models to enhance implicit sentiment classification. Approximately 10% accuracy gain on long reviews via structured CoT prompting and model-size tuning.</p>
  <div class="tags"><span>Python</span><span>PyTorch</span><span>Hugging Face</span><span>Flan-T5</span></div>
</div>

<div class="card">
  <h3>Dynamic Network Analysis</h3>
  <p class="meta">17-801 Dynamic Network Analysis · Prof. Kathleen Carley</p>
  <p>Analyzed digital traces of conspiracy theories and their correlation with offline violence using advanced network analysis techniques.</p>
  <div class="tags"><span>ORA</span><span>NetMapper</span><span>Python</span></div>
  <div class="pub-links"><a class="chip" href="{{ '/DNA_Syllabus_Spring_2024.pdf' | relative_url }}">Syllabus</a></div>
</div>

<div class="card">
  <h3>Soccer Game Outcome Prediction</h3>
  <p class="meta">IE 582 Statistical Learning for Data Mining · Asst. Prof. Mustafa Gökçe Baydoğan</p>
  <p>Developed predictive models for soccer game outcomes using historical game data and betting scores.</p>
  <div class="tags"><span>R</span><span>Feature extraction</span><span>Machine learning</span></div>
  <div class="pub-links"><a class="chip" href="{{ '/IE_582_Project.html' | relative_url }}">Report &amp; code</a></div>
</div>

<div class="card">
  <h3>Graph Algorithm Analysis</h3>
  <p class="meta">IE 456 Graph Algorithms and Applications · Assoc. Prof. Tınaz Ekim Aşıcı</p>
  <p>Implemented and compared degree sequence generation algorithms for graphs with different degree distributions.</p>
  <div class="tags"><span>C++</span><span>R</span></div>
  <div class="pub-links"><a class="chip" href="{{ '/IE_456_Project_Report.pdf' | relative_url }}">Report</a><a class="chip" href="https://github.com/orkunirsoy/orkunirsoy.github.io/tree/main/archived_projects/IE456ProjectCode">Code</a></div>
</div>

## Honors & fellowships

<ul class="honors">
{%- for h in site.data.honors %}
  <li><span class="muted">{{ h.year }}</span><span><strong>{{ h.title }}</strong>{% if h.org %}<br><span class="muted">{{ h.org }}</span>{% endif %}</span></li>
{%- endfor %}
</ul>
