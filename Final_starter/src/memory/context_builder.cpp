// src/memory/context_builder.cpp — YOU IMPLEMENT. Spec §4.4.

#include "memory/context_builder.h"
#include "util/min_heap.h"

ContextPlan select_context(const std::vector<ContextItem>& items,
                           std::size_t budget, std::size_t keep_recent) {
    // TODO: total the tokens; if they fit, keep everything. Otherwise push
    // every unprotected item onto a MinHeap keyed on (drop_rank(role), index)
    // and pop/drop until the total fits or the heap is empty.
    //
    // Clues:
    //  * Heap entries:  MinHeap<std::pair<int, std::size_t>> heap;
    //    std::pair compares .first, then .second, which is exactly
    //    "lowest rank first, then oldest first".
    //  * "The last keep_recent items" start at index items.size() - keep_recent,
    //    but these are unsigned: if keep_recent > items.size() that
    //    subtraction wraps around to a huge number. Handle that case first.
    //  * A vector<bool> keep(items.size(), true) makes the final pass easy:
    //    collect the indices still marked true, in ascending order.
    //  * total_tokens is the sum of the KEPT items; over_budget is
    //    total_tokens > budget.
    // std::size_t total = 0;
    // for (const auto& i : items){
    //     total+=items;
    // }
    // if (total <= budget){
    //     heap(keep_recent, )
    // }
    MinHeap<std::pair<int, std::size_t>> heap;
    std::size_t total_tokens = 0;
    ContextPlan fit; 
    for (const auto& i : items){
        total_tokens += i.tokens;
    }
    if (total_tokens <= budget){
        for (std::size_t i = 0; i < items.size(); i++){
            fit.keep.push_back(i);
        }

        fit.total_tokens = total_tokens;
        return fit;
    } else {
         if (keep_recent >= items.size()){
            for (std::size_t i = 0; i < items.size(); i++){
                fit.keep.push_back(i);
            }
            fit.over_budget = true;
            fit.total_tokens = total_tokens;
            return fit;

        } else {
            for (std::size_t i = items.size() - keep_recent - 1; i >= 0; i--){
                if (items[i].role != Role::System && items[i].pinned != true){

                    heap(drop_rank(items[i].role),i);
                }
            }
        }
    }

    (void)items;
    (void)budget;
    (void)keep_recent;
    return {};
}
