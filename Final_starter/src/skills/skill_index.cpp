// src/skills/skill_index.cpp — YOU IMPLEMENT. Spec §6.3.

#include "skills/skill_index.h"
#include "util/min_heap.h"
#include "util/text.h"

void SkillIndex::add(std::size_t doc_id, std::string_view text) {
    // TODO
    // Clue: use unique_tokens(text), not tokenize(text): a word that appears
    // twice in one document must post its doc_id only once.
    auto temp = unique_tokens(text);
    for (const auto&item : temp){
        postings_[item].push_back(doc_id);
    }
    //temp.push(doc_id);
    //(void)doc_id;
    //(void)text;
}

const std::vector<std::size_t>* SkillIndex::postings(std::string_view word) const {
    // TODO
    // Clue: the map's keys are std::string, so find(word) with a
    // string_view does not compile in C++17: use find(std::string(word)).
    // Return the address of the vector inside the map (&it->second).
    if (postings_.find(std::string(word)) != postings_.end()){
        auto it = postings_.find(std::string(word));
        return &it->second;
    } else {
        return nullptr;
    }
    //(void)word;
    //return nullptr;
}

std::size_t SkillIndex::word_count() const noexcept {
    return postings_.size();
    // TODO
    //return 0;
}

std::vector<std::size_t> SkillIndex::search(std::string_view query, std::size_t k) const {
    // TODO: score documents using only the posting lists of the query's
    // words, then rank with top_k().
    // Clues:
    //  * Count with  std::unordered_map<std::size_t, std::size_t> score;
    //    walking the posting list of each word of unique_tokens(query)
    //    (a repeated query word counts once).
    //  * Put (score, doc_id) pairs in a vector and call top_k with a
    //    comparator meaning "a is WORSE than b": lower score is worse; with
    //    equal scores the LARGER doc_id is worse.
    //  * Don't copy the lambda in skill_index_linear.cpp: that one is a
    //    std::sort order ("a comes first"), the opposite direction.
    std::vector<std::size_t> empty;
    std::vector<std::size_t> answer;

    if (k == 0){
        return empty;
    }
    auto temp = unique_tokens(query);
    std::unordered_map<std::size_t, std::size_t>score;

    //std::vector<std::size_t> top_k;
    for (const auto& item: temp){


            const std::vector<std::size_t>* ptr = postings(item);
            if (ptr == nullptr){
                continue;
            }
            for (std::size_t p : *ptr){
                score[p]++;
            }
    }

    std::vector<std::pair<std::size_t, std::size_t>> pairs;
    for (const auto& item: score){
        pairs.push_back({item.second, item.first});

    }
    auto worst = [](const std::pair<std::size_t, std::size_t>& one, const std::pair<std::size_t, std::size_t>& two){
        if (one.first < two.first){

            return true;
        } else if (one.first == two.first){
            if (one.second < two.second){
                return false;
            } else {
                return true;
            }
            return false;
        }
        return false;
    };
    auto order = top_k(pairs, k, worst);
    for (const auto& item: order){
        answer.push_back(item.second);
    }
    return answer;

}
