/*!
 *  Copyright (c) 2016 by Contributors
 * \file ir_mutator.h
 * \brief Defines general IRMutation pass
 */
#ifndef TVM_IR_MUTATOR_H_
#define TVM_IR_MUTATOR_H_

#include <tvm/ir_functor.h>
#include <unordered_map>
#include "./expr.h"
#include "./ir.h"

namespace tvm {
namespace ir {
/*!
 * \brief a base class for mutator to iterative mutate the IR
 *
 *  This IRMutator is implemented via Visitor Pattern.
 *  Also you can implement via IRFunctor.
 *  This enables easy extensions of possible new Node.
 *  It also makes changing return types easier.
 *
 * \note If you want to return a different type other than Expr and Stmt,
 *       Simply following the same pattern as IRMutator and create a seperate class.
 * \sa IRFunctor
 */
class IRMutator {
 public:
  /*!
   * \brief mutate expression
   * \return the mutated expr
   */
  virtual Expr Mutate(Expr expr) {
    static const FMutateExpr& f = vtable_expr();
    return f(expr, expr, this);
  }
  /*!
   * \brief mutate expression
   * \return the mutated stmt
   */
  virtual Stmt Mutate(Stmt stmt) {
    static const FMutateStmt& f = vtable_stmt();
    return f(stmt, stmt, this);
  }
  /*! \brief destructor */
  virtual ~IRMutator() {}
  /*! \brief functor type of expr mutation */
  using FMutateExpr = IRFunctor<Expr(const NodeRef&, const Expr&, IRMutator*)>;
  /*! \brief functor type of stmt mutation */
  using FMutateStmt = IRFunctor<Stmt(const NodeRef&, const Stmt&, IRMutator*)>;
  /*! \return internal vtable of expr */
  static FMutateExpr& vtable_expr();  // NOLINT(*)
  /*! \return internal stmt of expr */
  static FMutateStmt& vtable_stmt();  // NOLINT(*)
  // Set of overloadable functions
  // The underscore allows Mutate not to be shadowed by inheritance
  virtual Stmt Mutate_(const LetStmt* op, const Stmt& s);
  virtual Stmt Mutate_(const AttrStmt* op, const Stmt& s);
  virtual Stmt Mutate_(const IfThenElse* op, const Stmt& s);
  virtual Stmt Mutate_(const For* op, const Stmt& s);
  virtual Stmt Mutate_(const Allocate* op, const Stmt& s);
  virtual Stmt Mutate_(const Store* op, const Stmt& s);
  virtual Stmt Mutate_(const Free* op, const Stmt& s);
  virtual Stmt Mutate_(const AssertStmt* op, const Stmt& s);
  virtual Stmt Mutate_(const ProducerConsumer* op, const Stmt& s);
  virtual Stmt Mutate_(const Provide* op, const Stmt& s);
  virtual Stmt Mutate_(const Realize* op, const Stmt& s);
  virtual Stmt Mutate_(const Prefetch* op, const Stmt& s);
  virtual Stmt Mutate_(const Block* op, const Stmt& s);
  virtual Stmt Mutate_(const Evaluate* op, const Stmt& s);

  virtual Expr Mutate_(const Variable* op, const Expr& e);
  virtual Expr Mutate_(const Load* op, const Expr& e);
  virtual Expr Mutate_(const Let* op, const Expr& e);
  virtual Expr Mutate_(const Call* op, const Expr& e);
  virtual Expr Mutate_(const Add* op, const Expr& e);
  virtual Expr Mutate_(const Sub* op, const Expr& e);
  virtual Expr Mutate_(const Mul* op, const Expr& e);
  virtual Expr Mutate_(const Div* op, const Expr& e);
  virtual Expr Mutate_(const Mod* op, const Expr& e);
  virtual Expr Mutate_(const Min* op, const Expr& e);
  virtual Expr Mutate_(const Max* op, const Expr& e);
  virtual Expr Mutate_(const EQ* op, const Expr& e);
  virtual Expr Mutate_(const NE* op, const Expr& e);
  virtual Expr Mutate_(const LT* op, const Expr& e);
  virtual Expr Mutate_(const LE* op, const Expr& e);
  virtual Expr Mutate_(const GT* op, const Expr& e);
  virtual Expr Mutate_(const GE* op, const Expr& e);
  virtual Expr Mutate_(const And* op, const Expr& e);
  virtual Expr Mutate_(const Or* op, const Expr& e);
  virtual Expr Mutate_(const Reduce* op, const Expr& e);
  virtual Expr Mutate_(const Cast* op, const Expr& e);
  virtual Expr Mutate_(const Not* op, const Expr& e);
  virtual Expr Mutate_(const Select* op, const Expr& e);
  virtual Expr Mutate_(const Ramp* op, const Expr& e);
  virtual Expr Mutate_(const Broadcast* op, const Expr& e);
  virtual Expr Mutate_(const IntImm* op, const Expr& e);
  virtual Expr Mutate_(const UIntImm* op, const Expr& e);
  virtual Expr Mutate_(const FloatImm* op, const Expr& e);
  virtual Expr Mutate_(const StringImm* op, const Expr& e);
  virtual Expr Mutate_(const Shuffle* op, const Expr& e);
};

}  // namespace ir
}  // namespace tvm
#endif  // TVM_IR_MUTATOR_H_
